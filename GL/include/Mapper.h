#ifndef MAPPER_GL_H
#define MAPPER_GL_H
#include <memory>
#include "GLExport.h"

class GL_API Mapper
{
public:
  Mapper();
  virtual ~Mapper();

  virtual void render() = 0;

private:
  struct Private;
  std::unique_ptr<Private> mPrivate;
};
#endif // MAPPER_GL_H