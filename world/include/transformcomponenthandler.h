#ifndef TRANSFORMCOMPONENTHANDLER_H
#define TRANSFORMCOMPONENTHANDLER_H

#include "componenthandler.hpp"
#include "transformcomponent.h"


class TransformComponentHandler : public TypedComponentHandler<TransformComponent>
{
public:
  TransformComponentHandler();

  // ComponentHandler interface
public:
  virtual void handle(std::shared_ptr<TransformComponent> &c, const double &delta) override;
};

#endif // TRANSFORMCOMPONENTHANDLER_H
