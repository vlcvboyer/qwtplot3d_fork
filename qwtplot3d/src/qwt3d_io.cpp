#include <time.h>

#include "qwt3d_plot.h"
#include "qwt3d_io_gl2ps.h"
#include "qwt3d_io_reader.h"


using namespace Qwt3D;

static Qwt3D::IO qwt3diodummy;


/*! 
  Registers a new IO::Function for data input.\n
  Every call overwrites a formerly registered handler for the same format string
  (case sensitive).
*/
bool IO::defineInputHandler(QString const& format, IO::Function func)
{
  return add_unique(rlist(), Entry(format, func));
}

/*! 
  Registers a new Functor for data input.\n
  Every call overwrites a formerly registered handler for the same format string
  (case sensitive).
*/
bool IO::defineInputHandler(QString const& format, IO::Functor const& func)
{
  return add_unique(rlist(), Entry(format, func));
}

/*! 
  Registers a new IO::Function for data output.  
  Every call overwrites a formerly registered handler for the same format string
  (case sensitive).
 */
bool IO::defineOutputHandler(QString const& format, IO::Function func)
{
  return add_unique(wlist(), Entry(format, func));
}

/*! 
  Registers a new Functor for data output.\n
  Every call overwrites a formerly registered handler for the same format string
  (case sensitive).
*/
bool IO::defineOutputHandler(QString const& format, IO::Functor const& func)
{
  return add_unique(wlist(), Entry(format, func));
}

/*!
  Returns a pointer to a reading IO::Function if such a function has been registered by 
  defineInputHandler and 0 else. 
*/
bool IO::load(Plot3D* plot, QString const& fname, QString const& format)
{
  IT it = IO::find(rlist(), format);

  if (it == rlist().end())
    return false;

  return (*it->iofunc)(plot, fname);
}

/*!
  Returns a pointer to a writing IO::Function if such a function has been registered by 
  defineOutputHandler and 0 else. 
*/
bool IO::save(Plot3D* plot, QString const& fname, QString const& format)
{
  IT it = IO::find(wlist(), format);

  if (it == wlist().end())
    return false;

  return (*it->iofunc)(plot, fname);
}

/*!
  Returns a list of currently registered input formats. 
*/
QStringList IO::inputFormatList()
{
  QStringList list;
  for ( IT it = rlist().begin(); it!=rlist().end(); ++it )
    list.append(it->fmt);
  
  return list;
}

/*!
  Returns a list of currently registered output formats. 
*/
QStringList IO::outputFormatList()
{
  QStringList list;  
  for ( IT it = wlist().begin(); it!=wlist().end(); ++it )
    list.append(it->fmt);
  
  return list;
}

/*! 
  Returns the input functor in charge for format and 0 if non-existent. 
*/
IO::Functor* IO::inputHandler(QString const& format)
{
  IO::IT it = IO::find(rlist(), format);
  
  if (it==rlist().end())
    return 0;

  return it->iofunc;
}

/*! 
  Returns the output functor in charge for format and 0 if non-existent. 
*/
IO::Functor* IO::outputHandler(QString const& format)
{
  IO::IT it = IO::find(wlist(), format);
  
  if (it==wlist().end())
    return 0;

  return it->iofunc;
}

bool QtPixmap::operator()(Plot3D* plot, QString const& fname)
{
  QImage im = plot->grabFrameBuffer(true);
  return im.save(fname, (const char*)fmt_.local8Bit());
}


void IO::setupHandler()
{
  QStringList list = QImage::outputFormatList();
  QStringList::Iterator it = list.begin();
  QtPixmap qtpix;
  while( it != list.end() ) 
  {
    qtpix.fmt_ = *it;
    defineOutputHandler(*it, qtpix);
    ++it;
  }
  GL2PS vecfunc; 
  vecfunc.setCompressed(false);
  vecfunc.setFormat("EPS");
  defineOutputHandler("EPS", vecfunc);
  vecfunc.setFormat("PS");
  defineOutputHandler("PS", vecfunc);
  
#ifdef GL2PS_HAVE_ZLIB
  vecfunc.setCompressed(true);
  vecfunc.setFormat("EPS_GZ");
  defineOutputHandler("EPS_GZ", vecfunc);
  vecfunc.setFormat("PS_GZ");
  defineOutputHandler("PS_GZ", vecfunc);
#endif
  vecfunc.setFormat("PDF");
  defineOutputHandler("PDF", vecfunc);

  defineInputHandler("mes", NativeReader());
  defineInputHandler("MES", NativeReader());
}

/*!
	\deprecated  Use Plot3D::save or IO::save instead.
	
  Writes vector data supported by gl2ps. The corresponding format types are "EPS","PS"or "PDF".
  If zlib has been configured this will be extended by "EPS_GZ" and "PS_GZ". 
	\b Beware: BSPSORT turns out to behave very slowly and memory consuming, especially in cases where
	many polygons appear. It is still more exact than SIMPLESORT.
*/
bool Plot3D::saveVector(QString const& fileName, QString const& format, GL2PS::TEXTMODE text, GL2PS::SORTMODE sortmode)
{
  if (format == "EPS" || format == "EPS_GZ" || format == "PS" 
    || format == "PS_GZ" || format == "PDF")
  {  
    GL2PS* gl2ps = (GL2PS*)IO::outputHandler(format);
    if (gl2ps)
    {
      gl2ps->setSortMode(sortmode);
      gl2ps->setTextMode(text);
    }
    return IO::save(this, fileName, format);
  }
  return false;
}	
/*!
	\deprecated  Use Plot3D::save or IO::save instead.
  
  Saves the framebuffer to the file fileName using one of the image file formats supported by Qt.
*/
bool Plot3D::savePixmap(QString const& fileName, QString const& format)
{
  if (format == "EPS" || format == "EPS_GZ" || format == "PS" 
    || format == "PS_GZ" || format == "PDF")
    return false;
  
  return IO::save(this, fileName, format);
}

/*! 
  Saves content in one of the registered output formats. To modify the 
  behaviour for more complex output handling use IO::outputHandler.
*/
bool Plot3D::save(QString const& fileName, QString const& format)
{
  return IO::save(this, fileName, format);
}
