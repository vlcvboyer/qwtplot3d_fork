#ifndef __DRAWABLE_H__
#define __DRAWABLE_H__


#include <list>
#include "qwt3d_global.h"
#include "qwt3d_types.h"

namespace Qwt3D
{

//! ABC for Drawables
class QWT3D_EXPORT Drawable 
{

public:

	virtual ~Drawable() = 0;
	
	virtual void draw();

	virtual void saveGLState();
	virtual void restoreGLState();

	void attach(Drawable*);
	void detach(Drawable*);
	void detachAll();
	
	virtual void setColor(double r, double g, double b, double a = 1);	
	virtual void setColor(Qwt3D::RGBA rgba);	

protected:
	
	Qwt3D::RGBA color;
	void Enable(GLenum what, GLboolean val);
	

private:

	GLboolean ls;
	GLboolean pols;
	GLint polmode[2];
	GLfloat lw;
	GLint blsrc, bldst;
	GLdouble col[4];
	GLint pattern, factor;
	GLboolean sallowed;
	GLboolean tex2d;
	GLint matrixmode;

	std::list<Drawable*> dlist;

};

} // ns

#endif // __DRAWABLE_H__
