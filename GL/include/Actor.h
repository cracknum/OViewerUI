#ifndef ACTOR_GL_H
#define ACTOR_GL_H
#include <memory>
#include "GLExport.h"
class Mapper;
class GL_API Actor
{
public:
  Actor();
  virtual ~Actor();
  void setMapper(const std::shared_ptr<Mapper>& mapper);
  virtual void render() = 0;

private:
  struct Private;
  std::unique_ptr<Private> mPrivate;
};
#endif // ACTOR_GL_H