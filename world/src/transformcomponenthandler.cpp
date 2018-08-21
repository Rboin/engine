#include "transformcomponenthandler.h"

TransformComponentHandler::TransformComponentHandler()
{

}

void TransformComponentHandler::handle(std::shared_ptr<TransformComponent> &c, const double &delta)
{
  c->update(delta);
}
