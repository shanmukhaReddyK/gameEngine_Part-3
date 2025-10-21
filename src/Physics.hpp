#pragma once

#include "Entity.hpp"

namespace Physics {

    Vec2f GetOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b ) {
        //return the overlap rectangle size of the bounding boxes of entity a and b
        Vec2f delta = {std::abs(a->get<CTransform>().pos.x-b->get<CTransform>().pos.x),std::abs(a->get<CTransform>().pos.y-b->get<CTransform>().pos.y)} ;
        float ox = a->get<CBoundingBox>().halfSize.x + b->get<CBoundingBox>().halfSize.x - delta.x;
        float oy = a->get<CBoundingBox>().halfSize.y + b->get<CBoundingBox>().halfSize.y - delta.y;
        return Vec2f(ox,oy); 
    }
    
    Vec2f GetPreviousOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b ) {
        //return the previous overlap rectangle size of the bounding boxes of entity a and b
        // previous overlap use entity's previous position
        Vec2f delta = {std::abs(a->get<CTransform>().prevPos.x-b->get<CTransform>().prevPos.x),std::abs(a->get<CTransform>().prevPos.y-b->get<CTransform>().prevPos.y)} ;
        float ox = a->get<CBoundingBox>().halfSize.x + b->get<CBoundingBox>().halfSize.x - delta.x;
        float oy = a->get<CBoundingBox>().halfSize.y + b->get<CBoundingBox>().halfSize.y - delta.y;
        return Vec2f(ox,oy);
    }
}