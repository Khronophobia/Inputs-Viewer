#include "NodeTransform.hpp"

using namespace geode::prelude;

void NodeTransform::applyTransform(CCNode* node) {
    node->setPosition(position);
    node->setScale(scale);
    node->setVisible(isVisible);
}

void NodeTransform::setValues(CCNode* node) {
    position = node->getPosition();
    scale = node->getScale();
    isVisible = node->isVisible();
}