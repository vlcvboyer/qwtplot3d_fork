#ifndef __AXIS_H__
#define __AXIS_H__

#include "qwt3d_global.h"
#include "qwt3d_labelpixmap.h"

namespace Qwt3D
{

class LabelTexture;

//! Autoscalable axis with caption
class QWT3D_EXPORT Axis : public Drawable
{

public:

	explicit Axis();
	Axis(Qwt3D::Triple beg, Qwt3D::Triple end);
	~Axis();
	
	virtual void draw();

	void setPosition(const Qwt3D::Triple& beg, const Qwt3D::Triple& end);
	void position(Qwt3D::Triple& beg, Qwt3D::Triple& end) const {beg = beg_; end = end_;}
	void setTicLength(double majorl, double minorl);
	void ticLength(double& majorl, double& minorl) const {majorl = lmaj_; minorl = lmin_;}
	void setTicOrientation(double tx, double ty, double tz);
	void setTicOrientation(const Qwt3D::Triple& val);
	Qwt3D::Triple ticOrientation() const { return orientation_;}
	void setSymmetricTics( bool b) { symtics_ = b;}
	
	void setLabelFont(QString const& family, int pointSize, int weight = QFont::Normal, bool italic = false);
	void setLabelFont(QFont const& font);
  void setLabelString(QString const& name);
	void setLabelPosition(const Qwt3D::Triple& pos, LabelPixmap::ANCHOR);
	void setLabelColor(Qwt3D::RGBA col);
	void setLabel(bool d) {drawLabel_ = d;}

	void setScale(bool d) {drawTics_ = d;}
	void setNumbers(bool d) {drawNumbers_ = d;}
	bool numbers() const {return drawNumbers_;}
	void setNumberColor(Qwt3D::RGBA col);
	Qwt3D::RGBA numberColor() const {return numbercolor_;}
	void setNumberFont(QString const& family, int pointSize, int weight = QFont::Normal, bool italic = false);
	void setNumberFont(QFont const&);
	void setNumberAnchor(LabelPixmap::ANCHOR a) { scaleNumberAnchor_ = a;}

	void setAutoScale(bool val = true) {autoscale_ = val;};
	bool autoScale() const { return autoscale_;}

	void setMajors(int val);
	void setMinors(int val);
	int majors() const { return tmaj_; }
	int minors() const { return tmin_; }

	void setLineWidth(double val, double majfac = 0.9, double minfac = 0.5);

	Qwt3D::Triple begin() const { return beg_; }
	Qwt3D::Triple end() const { return end_; }


	void setLimits(double start, double stop) {start_=start; stop_=stop;}

	
private:

	void init();
	void drawBase();
	void drawTics();
	void drawNumber(Qwt3D::Triple Pos, int mtic);

	void buildAutoScale(double& a, double& b);

	void drawTic(Qwt3D::Triple nadir, double length);
	
	
	LabelPixmap label_;
	std::vector<LabelPixmap> markerLabel_;

	Qwt3D::Triple beg_, end_;

	Qwt3D::Triple ncube_beg_, ncube_end_; //!< enclosing parallelepiped for axis numbering

	double start_, stop_, autostart_, autostop_;
	double lmaj_, lmin_;
	Qwt3D::Triple orientation_;

	int tmaj_, tmin_;

	double lineWidth_, majLineWidth_, minLineWidth_;
	bool symtics_;
	bool drawNumbers_, drawTics_, drawLabel_;
	bool autoscale_;
	QFont numberfont_;
	Qwt3D::RGBA  numbercolor_;
	bool simpleLabels_;

	void makeSimpleLabels(bool val) { simpleLabels_ = val;}
	bool simpleLables() const { return simpleLabels_;}


	LabelPixmap::ANCHOR scaleNumberAnchor_;
};

} // ns 

#endif