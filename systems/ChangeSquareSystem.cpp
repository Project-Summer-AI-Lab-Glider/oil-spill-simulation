//
// Created by arczipt on 17.08.2020.
//


#include <algorithm>
#include <iostream>

#include "ChangeSquareSystem.h"

void ChangeSquareSystem::update(sycl::queue& queue,
                                sycl::buffer<Cell::Params, 1>& cellParamsBuf,
                                sycl::buffer<OilPoint::Params, 1>& opParamsBuf,
                                sycl::buffer<OilComponent, 2>& opCompBuf,
                                int timestep) {
    queue.submit([&](sycl::handler& cgh){
        auto cellParamsI = cellParamsBuf.get_access<sycl::access::mode::read>(cgh);
        auto opParamsIO = opParamsBuf.get_access<sycl::access::mode::read_write>(cgh);

        int cellSize = config.cellSize;

        int rowNum = cells.getRow();
        int colNum = cells.getCol();

        cgh.parallel_for<class CSSUpdate>(sycl::range<1>(opParamsBuf.get_count()), [=](sycl::id<1> i){
            auto& op = opParamsIO[i];

            if(op.removed)
                return;

            double posX = op.position.x;
            double posY = op.position.y;
            int row = op.cellPos.x;
            int col = op.cellPos.y;

            int newRow = (int) (posY / cellSize);
            int newCol = (int) (posX / cellSize);

            auto c1 = (newRow != row || newCol != col);
            auto c2 = (newRow < rowNum && newRow > 0 && newCol < colNum && newCol > 0);

            op.cellPos.x = c1*c2*newRow + (!c1)*op.cellPos.x;
            op.cellPos.y = c1*c2*newCol + (!c1)*op.cellPos.y;

            op.removed = (c1 & !c2);
        });
    });
}
