#ifndef __COORDSYS_H__
#define __COORDSYS_H__

#include "axis.h"
#include "plane.h"

//! A coordinate system with different styles (BOX, FRAME)
class CoordinateSystem : public Drawable
{

public:
	
	explicit CoordinateSystem(Triple blb = Triple(0,0,0), Triple ftr = Triple(0,0,0), Qwt3d::COORDSTYLE = Qwt3d::BOX);
  ~CoordinateSystem();	
	
	void init(Triple beg = Triple(0,0,0), Triple end = Triple(0,0,0));
	void setStyle(Qwt3d::COORDSTYLE s,	Qwt3d::AXIS frame_1 = Qwt3d::X1, 
																			Qwt3d::AXIS frame_2 = Qwt3d::Y1, 
																			Qwt3d::AXIS frame_3 = Qwt3d::Z1);
	Qwt3d::COORDSTYLE style() const { return style_;}
	void setPosition(Triple first, Triple second); //!< first == front_left_bottom, second == back_right_top
	
	void setAxesColor(RGBA val);
	void setNumberFont(QString const& family, int pointSize, int weight = QFont::Normal, bool italic = false);
	void setNumberFont(QFont const& font);
	void setNumberColor(RGBA val);
	
	void setLabelFont(QString const& family, int pointSize, int weight = QFont::Normal, bool italic = false);
	void setLabelFont(QFont const& font);
	void setLabelColor(RGBA val);

	void setLineWidth(double val, double majfac = 1, double minfac = 0.6);
	void setTicLength(double major, double minor);
	void setAutoScale(bool val = true);

	Triple first() const { return first_;}
	Triple second() const { return second_;}

	void setAutoDecoration(bool val = true) {autodecoration_ = val;}
	bool autoDecoration() const { return autodecoration_;}

	void setLineSmooth(bool val = true) {smooth_ = val;} //!< draw smooth axes
	bool lineSmooth() const {return smooth_;}            //!< smooth axes ? 

	void draw();
	void postDraw();

	std::vector<Axis> axes;

private:

	void destroy();
	
	Triple first_, second_;
	Qwt3d::COORDSTYLE style_;
	
	double ared_, agreen_, ablue_; 
	double lineWidth_, majLineWidth_, minLineWidth_;

	bool smooth_;

	void positionateLabel(Axis& ax, LabelPixmap::ANCHOR an);
	
	void chooseAxesForAutoDecoration();
	void autoDecorateExposedAxis(Axis& ax, bool left);

	bool autodecoration_;
};

#endif