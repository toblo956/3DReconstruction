#ifndef _NON_LINEAR_H_
#define _NON_LINEAR_H_



#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <libs/levmar/levmar.h> //<<<---- numera p� sven.
#include "Camera.h"
#include "Estimate3D.h"
#include <math.h>
#include <fstream>

extern std::ofstream errorFile;
extern std::ofstream logFile;

namespace NonLinear
{
	
	struct goldStandardData
	{
		int nPoints;
		cv::Mat F;
		cv::Mat points1; 
		cv::Mat points2; 
	};
	
	struct goldNonLinData
	{
		int nPoints2D;
		int nPoints3D;

		std::vector<double>* params;

		
		
		cv::Mat F;
		cv::Mat K;
		std::vector<cv::Point2d> points1; 
		std::vector<cv::Point2d> points2; 
		cv::Mat points3D;
		cv::Mat C1;
		cv::Mat C2;
	};

	struct BAData
	{
		int nViews;
		int n3DPoints;
		
		double oneData;
		double stopThreshold;
		cv::Mat one;
		cv::Mat R;
		cv::Mat rVec;
		cv::Mat t;
		cv::Mat point2D;
		cv::Mat point3D;
		cv::Mat C;
		cv::Mat P;		

		cv::Mat K;
		std::vector<cv::Point3f> float2Ps;
		std::vector<cv::Point3f> float3DPs;
		std::vector<cv::Mat> rotations;
		std::vector<cv::Mat> translations;
		std::vector<std::vector<cv::Point2d>*> imagePoints;
		//cv::Mat allPoints3D;
		//std::vector<std::vector<cv::Mat>> visible3Dpoints;
		std::vector<std::vector<cv::Point3d*>> points3D;
		std::vector<Visible3DPoint>* all3DPoints;
		

	};



	class NonLinear
	{
	public:
		NonLinear(cv::Mat _K);
		NonLinear() {};
		void testFunc(double* params, double* residuals);
		void goldStandardRefine(cv::Mat F, std::vector<cv::Point2d> points1, std::vector<cv::Point2d> points2);
		cv::Mat goldNonLin(cv::Mat F, cv::Mat C1, cv::Mat C2, cv::Mat point3D, std::vector<cv::Point2d> points1, std::vector<cv::Point2d> points2);
		void BundleAdjust(std::list<Camera*>& views, std::vector<Visible3DPoint>* all3DPoints, double stopThreshold = 0);
		
	public:
		// Hard-coded in constructor
		cv::Mat K;

		
	};
	void PnPSolver(Camera& cam);
	void PnPSolverOCV(Camera & cam, std::vector<cv::Point2d> & point2d, std::vector<cv::Point3d> & point3d, std::vector<int> & inlierIndices);
}


#endif