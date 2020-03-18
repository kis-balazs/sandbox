// OpenCVApplication.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "common.h"
#include <queue>
#include <random>
#include <fstream>

using namespace std;


void testOpenImage()
{
	char fname[MAX_PATH];
	while(openFileDlg(fname))
	{
		Mat src; // clasa din OpenCV, e o matrice cu size variabil pe orice tip de date, aici e doar o declaratie
		src = imread(fname); // citim imaginea. fname este calea catre fisier
		imshow("image",src); // ne arata imaginea, primul parametru este numele ferestrei, iar src e matricea unde a fost citita imaginea
		waitKey();
	}
}

void testOpenImagesFld()
{
	char folderName[MAX_PATH];
	if (openFolderDlg(folderName)==0)
		return;
	char fname[MAX_PATH];
	FileGetter fg(folderName,"bmp");
	while(fg.getNextAbsFile(fname))
	{
		Mat src;
		src = imread(fname);
		imshow(fg.getFoundFileName(),src);
		if (waitKey()==27) //ESC pressed
			break;
	}
}

void testImageOpenAndSave()
{
	Mat src, dst;

	src = imread("Images/Lena_24bits.bmp", CV_LOAD_IMAGE_COLOR);	// Read the image

	if (!src.data)	// Check for invalid input
	{
		printf("Could not open or find the image\n");
		return;
	}

	// Get the image resolution
	Size src_size = Size(src.cols, src.rows);

	// Display window
	const char* WIN_SRC = "Src"; //window for the source image
	namedWindow(WIN_SRC, CV_WINDOW_AUTOSIZE);
	cvMoveWindow(WIN_SRC, 0, 0);

	const char* WIN_DST = "Dst"; //window for the destination (processed) image
	namedWindow(WIN_DST, CV_WINDOW_AUTOSIZE);
	cvMoveWindow(WIN_DST, src_size.width + 10, 0);

	cvtColor(src, dst, CV_BGR2GRAY); //converts the source image to a grayscale one

	imwrite("Images/Lena_24bits_gray.bmp", dst); //writes the destination to file

	imshow(WIN_SRC, src);
	imshow(WIN_DST, dst);

	printf("Press any key to continue ...\n");
	waitKey(0);
}

void testNegativeImage()
{
	char fname[MAX_PATH];
	while(openFileDlg(fname))
	{
		double t = (double)getTickCount(); // Get the current time [s]
		
		Mat src = imread(fname,CV_LOAD_IMAGE_GRAYSCALE);
		int height = src.rows;
		int width = src.cols;
		Mat dst = Mat(height,width,CV_8UC1);
		// Asa se acceseaaza pixelii individuali pt. o imagine cu 8 biti/pixel
		// Varianta ineficienta (lenta)
		for (int i=0; i<height; i++)
		{
			for (int j=0; j<width; j++)
			{
				uchar val = src.at<uchar>(i,j);
				uchar neg = MAX_PATH-val;
				dst.at<uchar>(i,j) = neg;
			}
		}

		// Get the current time again and compute the time difference [s]
		t = ((double)getTickCount() - t) / getTickFrequency();
		// Print (in the console window) the processing time in [ms] 
		printf("Time = %.3f [ms]\n", t * 1000);

		imshow("input image",src);
		imshow("negative image",dst);
		waitKey();
	}
}

void testParcurgereSimplaDiblookStyle()
{
	char fname[MAX_PATH];
	while (openFileDlg(fname))
	{
		Mat src = imread(fname, CV_LOAD_IMAGE_GRAYSCALE);
		int height = src.rows;
		int width = src.cols;
		Mat dst = src.clone();

		double t = (double)getTickCount(); // Get the current time [s]

		// the fastest approach using the “diblook style”
		uchar *lpSrc = src.data;
		uchar *lpDst = dst.data;
		int w = (int) src.step; // no dword alignment is done !!!
		for (int i = 0; i<height; i++)
			for (int j = 0; j < width; j++) {
				uchar val = lpSrc[i*w + j];
				lpDst[i*w + j] = 255 - val;
			}

		// Get the current time again and compute the time difference [s]
		t = ((double)getTickCount() - t) / getTickFrequency();
		// Print (in the console window) the processing time in [ms] 
		printf("Time = %.3f [ms]\n", t * 1000);

		imshow("input image",src);
		imshow("negative image",dst);
		waitKey();
	}
}

void testColor2Gray()
{
	char fname[MAX_PATH];
	while(openFileDlg(fname))
	{
		Mat src = imread(fname);

		int height = src.rows;
		int width = src.cols;

		Mat dst = Mat(height,width,CV_8UC1);

		// Asa se acceseaaza pixelii individuali pt. o imagine RGB 24 biti/pixel
		// Varianta ineficienta (lenta)
		for (int i=0; i<height; i++)
		{
			for (int j=0; j<width; j++)
			{
				Vec3b v3 = src.at<Vec3b>(i,j);
				uchar b = v3[0];
				uchar g = v3[1];
				uchar r = v3[2];
				dst.at<uchar>(i,j) = (r+g+b)/3;
			}
		}
		
		imshow("input image",src);
		imshow("gray image",dst);
		waitKey();
	}
}

void testBGR2HSV()
{
	char fname[MAX_PATH];
	while (openFileDlg(fname))
	{
		Mat src = imread(fname);
		int height = src.rows;
		int width = src.cols;

		// Componentele d eculoare ale modelului HSV
		Mat H = Mat(height, width, CV_8UC1);
		Mat S = Mat(height, width, CV_8UC1);
		Mat V = Mat(height, width, CV_8UC1);

		// definire pointeri la matricele (8 biti/pixeli) folosite la afisarea componentelor individuale H,S,V
		uchar* lpH = H.data;
		uchar* lpS = S.data;
		uchar* lpV = V.data;

		Mat hsvImg;
		cvtColor(src, hsvImg, CV_BGR2HSV);

		// definire pointer la matricea (24 biti/pixeli) a imaginii HSV
		uchar* hsvDataPtr = hsvImg.data;

		for (int i = 0; i<height; i++)
		{
			for (int j = 0; j<width; j++)
			{
				int hi = i*width * 3 + j * 3;
				int gi = i*width + j;

				lpH[gi] = hsvDataPtr[hi] * 510 / 360;		// lpH = 0 .. 255
				lpS[gi] = hsvDataPtr[hi + 1];			// lpS = 0 .. 255
				lpV[gi] = hsvDataPtr[hi + 2];			// lpV = 0 .. 255
			}
		}

		imshow("input image", src);
		imshow("H", H);
		imshow("S", S);
		imshow("V", V);

		waitKey();
	}
}

void testResize()
{
	char fname[MAX_PATH];
	while(openFileDlg(fname))
	{
		Mat src;
		src = imread(fname);
		Mat dst1,dst2;
		//without interpolation
		resizeImg(src,dst1,320,false);
		//with interpolation
		resizeImg(src,dst2,320,true);
		imshow("input image",src);
		imshow("resized image (without interpolation)",dst1);
		imshow("resized image (with interpolation)",dst2);
		waitKey();
	}
}

void testCanny()
{
	char fname[MAX_PATH];
	while(openFileDlg(fname))
	{
		Mat src,dst,gauss;
		src = imread(fname,CV_LOAD_IMAGE_GRAYSCALE);
		double k = 0.4;
		int pH = 50;
		int pL = (int) k*pH;
		GaussianBlur(src, gauss, Size(5, 5), 0.8, 0.8);
		Canny(gauss,dst,pL,pH,3);
		imshow("input image",src);
		imshow("canny",dst);
		waitKey();
	}
}

void testVideoSequence()
{
	VideoCapture cap("Videos/rubic.avi"); // off-line video from file
	//VideoCapture cap(0);	// live video from web cam
	if (!cap.isOpened()) {
		printf("Cannot open video capture device.\n");
		waitKey(0);
		return;
	}
		
	Mat edges;
	Mat frame;
	char c;

	while (cap.read(frame))
	{
		Mat grayFrame;
		cvtColor(frame, grayFrame, CV_BGR2GRAY);
		Canny(grayFrame,edges,40,100,3);
		imshow("source", frame);
		imshow("gray", grayFrame);
		imshow("edges", edges);
		c = cvWaitKey(0);  // waits a key press to advance to the next frame
		if (c == 27) {
			// press ESC to exit
			printf("ESC pressed - capture finished\n"); 
			break;  //ESC pressed
		};
	}
}


void testSnap()
{
	VideoCapture cap(0); // open the deafult camera (i.e. the built in web cam)
	if (!cap.isOpened()) // openenig the video device failed
	{
		printf("Cannot open video capture device.\n");
		return;
	}

	Mat frame;
	char numberStr[256];
	char fileName[256];
	
	// video resolution
	Size capS = Size((int)cap.get(CV_CAP_PROP_FRAME_WIDTH),
		(int)cap.get(CV_CAP_PROP_FRAME_HEIGHT));

	// Display window
	const char* WIN_SRC = "Src"; //window for the source frame
	namedWindow(WIN_SRC, CV_WINDOW_AUTOSIZE);
	cvMoveWindow(WIN_SRC, 0, 0);

	const char* WIN_DST = "Snapped"; //window for showing the snapped frame
	namedWindow(WIN_DST, CV_WINDOW_AUTOSIZE);
	cvMoveWindow(WIN_DST, capS.width + 10, 0);

	char c;
	int frameNum = -1;
	int frameCount = 0;

	for (;;)
	{
		cap >> frame; // get a new frame from camera
		if (frame.empty())
		{
			printf("End of the video file\n");
			break;
		}

		++frameNum;
		
		imshow(WIN_SRC, frame);

		c = cvWaitKey(10);  // waits a key press to advance to the next frame
		if (c == 27) {
			// press ESC to exit
			printf("ESC pressed - capture finished");
			break;  //ESC pressed
		}
		if (c == 115){ //'s' pressed - snapp the image to a file
			frameCount++;
			fileName[0] = NULL;
			sprintf(numberStr, "%d", frameCount);
			strcat(fileName, "Images/A");
			strcat(fileName, numberStr);
			strcat(fileName, ".bmp");
			bool bSuccess = imwrite(fileName, frame);
			if (!bSuccess) 
			{
				printf("Error writing the snapped image\n");
			}
			else
				imshow(WIN_DST, frame);
		}
	}

}

void MyCallBackFunc(int event, int x, int y, int flags, void* param)
{
	//More examples: http://opencvexamples.blogspot.com/2014/01/detect-mouse-clicks-and-moves-on-image.html
	Mat* src = (Mat*)param;
	if (event == CV_EVENT_LBUTTONDOWN)
		{
			printf("Pos(x,y): %d,%d  Color(RGB): %d,%d,%d\n",
				x, y,
				(int)(*src).at<Vec3b>(y, x)[2],
				(int)(*src).at<Vec3b>(y, x)[1],
				(int)(*src).at<Vec3b>(y, x)[0]);
		}
}

void testMouseClick()
{
	Mat src;
	// Read image from file 
	char fname[MAX_PATH];
	while (openFileDlg(fname))
	{
		src = imread(fname);
		//Create a window
		namedWindow("My Window", 1);

		//set the callback function for any mouse event
		setMouseCallback("My Window", MyCallBackFunc, &src);

		//show the image
		imshow("My Window", src);

		// Wait until user press some key
		waitKey(0);
	}
}

void showHistogram(const std::string& name, int* hist, const int  hist_cols, const int hist_height)
{
	Mat imgHist(hist_height, hist_cols, CV_8UC3, CV_RGB(255, 255, 255)); // constructs a white image

	//computes histogram maximum
	int max_hist = 0;
	for (int i = 0; i<hist_cols; i++)
	if (hist[i] > max_hist)
		max_hist = hist[i];
	double scale = 1.0;
	scale = (double)hist_height / max_hist;
	int baseline = hist_height - 1;

	for (int x = 0; x < hist_cols; x++) {
		Point p1 = Point(x, baseline);
		Point p2 = Point(x, baseline - cvRound(hist[x] * scale));
		line(imgHist, p1, p2, CV_RGB(152, 143, 197)); // histogram bins colored in magenta
	}

	imshow(name, imgHist);
	waitKey(0);

}

void negative_image() {
	/*
		Mat img = imread("Images/cameraman.bmp", CV_LOAD_IMAGE_GRAYSCALE);
		for (int i = 0; i < img.rows; i++) {
			for (int j = 0; j < img.cols; j++)
			{
				img.at<uchar>(i, j) = 255 - img.at<uchar>(i, j);
			}
		}
		imshow("negative image", img);
		waitKey(0);
	*/
	Mat_<uchar> img = imread("Images/cameraman.bmp", CV_LOAD_IMAGE_GRAYSCALE);
	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++)
		{
			img(i, j) = 255 - img(i, j);
		}
	}
	imshow("negative image", img);
	waitKey(0);	
}

void change_gray_levels_additive() {
	Mat_<uchar> img = imread("Images/cameraman.bmp", CV_LOAD_IMAGE_GRAYSCALE);
	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++)
		{ 
			if (img(i, j) + 100 > 255) {
				img(i, j) = 255;
			}
			else if (img(i, j) < 0) {
				img(i, j) = 0;
			}
			else {
				img(i, j) += 100;
			}
		}
	}
	imshow("negative image additive", img);
	waitKey(0);
}

void change_gray_levels_multiplicative() {
	Mat_<uchar> img = imread("Images/cameraman.bmp", CV_LOAD_IMAGE_GRAYSCALE);
	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++)
		{
			if (img(i, j) * 2 > 255) {
				img(i, j) = 255;
			}
			else if (img(i, j) < 0) {
				img(i, j) = 0;
			}
			else {
				img(i, j) *= 3;
			}
		}
	}
	imshow("negative image multiplicative", img);
	waitKey(0);
}

void split_image() {
	Mat_<Vec3b> colorImg(256, 256);
	for (int i = 0; i < 256; i++) {
		for (int j = 0; j < 256; j++)
		{
			Vec3b pixel;
			if (i >= 0 && i < 128 && j >= 0 && j < 128) {
				pixel[0] = 255; // blue
				pixel[1] = 255; // green 
				pixel[2] = 255; // red
				colorImg(i, j) = pixel;
			}
			else if (i >=0 && i < 128 && j >= 128 && j < 256) {
				pixel[0] = 0;
				pixel[1] = 0;
				pixel[2] = 255;
				colorImg(i, j) = pixel;
			}
			else if (i >= 128 && i < 256 && j >= 0 && j < 128) {
				pixel[0] = 0;
				pixel[1] = 255;
				pixel[2] = 0;
				colorImg(i, j) = pixel;
			}
			else if (i >= 128 && i < 256 && j >= 128 && j < 256) {
				pixel[0] = 0;
				pixel[1] = 255;
				pixel[2] = 255;
				colorImg(i, j) = pixel;
			}
		}
	}
	imshow("splitt image", colorImg);
	waitKey(0);
}

void inverse_matrix() {
	float vals[9] = { 3,0,1,0,2,0,0,0,1};
	Mat invMat3(3,3,CV_32FC1,vals);
	invMat3 = invMat3.inv();
	std::cout << invMat3;
	std::cout << "\n";
}

void rotate_image() {
	Mat_<uchar> img = imread("Images/kids.bmp", CV_LOAD_IMAGE_GRAYSCALE);
	imshow("original image", img);
	Mat_<uchar> newImg(img.cols,img.rows);
	int iNewImg = img.rows;
	int jNewImg = img.cols;
	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			newImg(j, iNewImg-i-1) = img(i, j); //rotate right
			//newImg(jNewImg -1-j, i) = img(i, j); // rotate left
		}
	}
	imshow("new image", newImg);
	waitKey(0);
}

//task1
void RGBChannels() {
	Mat_<Vec3b> img = imread("Images/flowers_24bits.bmp");
	int m = img.rows;
	int n = img.cols;
	Mat_<uchar> imgB(m,n);
	Mat_<uchar> imgG(m,n);
	Mat_<uchar> imgR(m,n);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			imgB(i, j) = img(i, j)[0];
			imgG(i, j) = img(i, j)[1];
			imgR(i, j) = img(i, j)[2];
		}
	}
	imshow("initial", img);
	imshow("blue", imgB);
	imshow("green", imgG);
	imshow("red", imgR);
	waitKey(0);
}

//task2
void RGBtoGrayScale() {
	Mat_<Vec3b> imgRGB = imread("Images/flowers_24bits.bmp");
	int m = imgRGB.rows;
	int n = imgRGB.cols;
	Mat_<uchar> imgGS(m,n);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			imgGS(i, j) = (imgRGB(i, j)[0] + imgRGB(i, j)[1] + imgRGB(i, j)[2]) / 3;
		}
	}
	imshow("rgb", imgRGB);
	imshow("grayScale", imgGS);
	waitKey(0);
}

//task3
void GrayScaleToBW() {
	Mat_<uchar> imgGS = imread("Images/flowers_24bits.bmp",CV_LOAD_IMAGE_GRAYSCALE);
	int m = imgGS.rows;
	int n = imgGS.cols;
	int threshold;
	scanf("%d", &threshold);
	Mat_<uchar> imgBW(m, n);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (imgGS(i, j) < threshold) {
				imgBW(i, j) = 0;
			}
			else {
				imgBW(i, j) = 255;
			}
		}
	}
	imshow("grayScale", imgGS);
	imshow("bw", imgBW);
	waitKey(0);


}

//task4
void RGBtoHSV(){
	Mat_<Vec3b> imgRGB = imread("Images/flowers_24bits.bmp");
	int m = imgRGB.rows;
	int n = imgRGB.cols;
	Mat_<uchar> imgH(m, n);
	Mat_<uchar> imgS(m, n);
	Mat_<uchar> imgV(m, n);
	for (int i =0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			
			float b = (float) imgRGB(i, j)[0] / 255;
			float g = (float) imgRGB(i, j)[1] / 255;
			float r = (float) imgRGB(i, j)[2] / 255;

			float M = max(r, max(g, b));
			float m = min(r, min(g, b));
			float C = M - m;

			float V = M;
			
			float S;
			if (V != 0) {
				S = C / V;
			}
			else {
				S = 0;
			}

			float H;
			if (C != 0) {
				if (M == r) {
					H = 60 * (g - b) / C;
				}
				if (M == g) {
					H = 120 + 60 * (b - r) / C;
				}
				if (M == b) {
					H = 240 + 60 * (r - g) / C;
				}
			}
			else {
				H = 0;
			}

			if (H < 0) {
				H += 360;
			}

			imgH(i, j) = H * 255 / 360;
			imgS(i, j) = S * 255;
			imgV(i, j) = V * 255;
		}
	}

	imshow("initial", imgRGB);
	imshow("H", imgH);
	imshow("S", imgS);
	imshow("V", imgV);
	waitKey(0);

}

boolean isInside(Mat_<uchar> img, int i, int j) {
	if (i >= 0 && i < img.rows && j >= 0 && j < img.cols) {
		return true;
	}
	else {
		return false;
	}
}

int h[256] = { 0 };
float p[256] = { 0 };

void histogramComputation() {
	//Mat_<uchar> imgGS = imread("Images/cameraman.bmp", CV_LOAD_IMAGE_GRAYSCALE);
	Mat_<uchar> imgGS = imread("Images/Hawkes_Bay_NZ.bmp", CV_LOAD_IMAGE_GRAYSCALE);
	int m = imgGS.rows;
	int n = imgGS.cols;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			h[imgGS(i, j)]++;
		}
	}

	for (int j = 0; j < 256; j++) {
		p[j] = (float) h[j] / (m*n);
	}

}

float maxArray[256] = { 0 };
uchar valueToBeDisplayed(uchar value, float maxArray[256]) {
	int min1 = 0;
	int min2 = 0;

	for (int i = value; i < 255; i++) {
		min1++;
		if (maxArray[i] > 0)
			break;
	}

	for (int i = value; i > 0; i--) {
		min2++;
		if (maxArray[i] > 0)
			break;
	}

	if (min1 > min2) {
		return value-min2;
	}
	else {
		return value + min1;
	}
}

void multilevelThresholding() {
	Mat_<uchar> imgGS = imread("Images/cameraman.bmp", CV_LOAD_IMAGE_GRAYSCALE);
	int m = imgGS.rows;
	int n = imgGS.cols;

	Mat_<uchar> dest(m, n);

	int WH = 5;
	float TH = 0.0003;

	float localMaximum = 0;
	float v=0;
	float sum=0;
	for (int k = 0 + WH; k < 255 - WH; k++) {
		sum = 0;
		localMaximum = 0;

			for (int i = k - WH; i < k + WH; i++) {
			sum += p[i];
			if ( i!=k && p[i] > localMaximum) {
				localMaximum = p[i];
			}
		}
		v = sum / (float ) ((2 * WH) + 1);
		if (p[k] > v + TH && p[k]>localMaximum) {
			maxArray[k] = p[k];
		}
	}

maxArray[0] = 0;
maxArray[255] = 255;

for (int i = 0; i < 256; i++) {
	std::cout << maxArray[i];
}

for (int i = 0; i < m; i++) {
	for (int j = 0; j < n; j++) {
		dest(i, j) = valueToBeDisplayed(imgGS(i, j), maxArray);
	}
}

imshow("original", imgGS);
imshow("updated", dest);
waitKey(0);

 }

 void floyd() {
	 Mat_<uchar> imgGS = imread("Images/saturn.bmp", CV_LOAD_IMAGE_GRAYSCALE);
	 int m = imgGS.rows;
	 int n = imgGS.cols;

	 Mat_<uchar> dest = imgGS.clone();
	 Mat_<uchar> destFinal = imgGS.clone();

	 int WH = 5;
	 float TH = 0.0003;

	 float localMaximum = 0;
	 float v = 0;
	 float sum = 0;

	 for (int k = 0 + WH; k < 255 - WH; k++) {
		 sum = 0;
		 localMaximum = 0;

		 for (int i = k - WH; i < k + WH; i++) {
			 sum += p[i];
			 if (i != k && p[i] > localMaximum) {
				 localMaximum = p[i];
			 }
		 }
		 v = sum / (float)((2 * WH) + 1);
		 if (p[k] > v + TH && p[k] > localMaximum) {
			 maxArray[k] = p[k];
		 }
	 }

	 maxArray[0] = 0;
	 maxArray[255] = 255;

	 for (int i = 0; i < 256; i++) {
		 std::cout << maxArray[i];
	 }

	 for (int i = 0; i < m; i++) {
		 for (int j = 0; j < n; j++) {
			 dest(i, j) = valueToBeDisplayed(imgGS(i, j), maxArray);
		 }
	 }

	 uchar oldpixel, newpixel;
	 int error;
	 for (int i = 1; i < m - 1; i++) {
		 for (int j = 1; j < n - 1; j++) {
			 oldpixel = destFinal(i, j);
			 newpixel = valueToBeDisplayed(destFinal(i, j), maxArray);
			 destFinal(i, j) = newpixel;
			 error = oldpixel - newpixel;
			 destFinal(i, j + 1) = min(max(0, destFinal(i, j + 1) + 7 * error / 16), 255);
			 destFinal(i + 1, j - 1) = min(max(0, destFinal(i + 1, j - 1) + 3 * error / 16), 255);
			 destFinal(i + 1, j) = min(max(0, destFinal(i + 1, j) + 5 * error / 16), 255);
			 destFinal(i + 1, j + 1) = min(max(0, destFinal(i + 1, j + 1) + error / 16), 255);
		 }
	 }

	 imshow("original", imgGS);
	 imshow("updated", destFinal);
	 waitKey(0);

 }

 void geometrical_features_function(int event, int x, int y, int flags, void* param)
 {
	 //More examples: http://opencvexamples.blogspot.com/2014/01/detect-mouse-clicks-and-moves-on-image.html
	 Mat* src = (Mat*)param;
	 int area = 0;
	 if (event == CV_EVENT_LBUTTONDBLCLK)
	 {

		 printf("Pos(x,y): %d,%d  Color(RGB): %d,%d,%d\n",
			 x, y,
			 (int)(*src).at<Vec3b>(y, x)[2],
			 (int)(*src).at<Vec3b>(y, x)[1],
			 (int)(*src).at<Vec3b>(y, x)[0]);

		 // compute area
		 for (int i = 0; i < src->rows; i++) {
			 for (int j = 0; j < src->cols; j++) {
				 if ( src->at<Vec3b>(i, j) == src->at<Vec3b>(y,x) ){
					 area++;
				 }
			}
		}
		 printf("Area: %d\n", area);
		 // compute area

		 // compute center of mass
		 int centerR=0;
		 int centerC=0;
		 for (int i = 0; i < src->rows; i++) {
			 for (int j = 0; j < src->cols; j++) {
				 if (src->at<Vec3b>(i, j) == src->at<Vec3b>(y, x)) {
					 centerR += i;
					 centerC += j;
				 }
			 }
		 }
		 centerR = centerR / area;
		 centerC = centerC / area;
		 printf("center r: %d\n", centerR);
		 printf("center c: %d\n", centerC);
		 // compute center of mass

		 //compute axis of elongation
		 float angle=0;
		 float radiansAngle=0;
		 int Y = 0;
		 int X = 0; 
		 for (int i = 0; i < src->rows; i++) {
			 for (int j = 0; j < src->cols; j++) {
				 if (src->at<Vec3b>(i, j) == src->at<Vec3b>(y, x)) {
					 Y += (i - centerR)*(j - centerC);
					 X += (j - centerC)*(j - centerC) - (i-centerR)*(i-centerR);
				 }
			 }
		 }
	
		 angle = atan2(2*Y, X) / 2;
		 if (angle < 0) {
			 angle += CV_PI;
		 }
		 radiansAngle = angle * 180 / CV_PI;
		 printf("Elongation: %f\n", radiansAngle);
		 //compute axis of elongation

		 // compute the perimeter
		 int perimeter = 0;
		 bool per = false;
		 for (int i = 0; i < src->rows; i++) {
			 for (int j = 0; j < src->cols; j++) {
				 if (src->at<Vec3b>(i, j) == src->at<Vec3b>(y, x)) {
					 per = false;
					 for (int m = -1; m <= 1; m++) {
						 for (int n = -1; n <= 1; n++) {
							 if (src->at<Vec3b>(i, j) != src->at<Vec3b>(i + m, j + n)) {
								 per = true;
							 }
						 }
					 }
					 if (per) {
						 perimeter++;
					 }
				 }
			 }
		 }
		 printf("Perimeter: %f\n", perimeter* CV_PI / 4);
		 // compute the perimeter

		 // compute thinness ratio
		 float thinnesssRatio = 4 * CV_PI * area / ((perimeter* CV_PI / 4)*(perimeter* CV_PI / 4));
		 printf("Thinness Ratio: %f\n", thinnesssRatio);
		 // compute thinness ratio

		 // compute aspect ratio
		 int cMax = 0;
		 int cMin = src->cols;
		 int rMax = 0;
		 int rMin = src->rows;
		 float aspectRatio = 0;
		 for (int i = 0; i < src->rows; i++) {
			 for (int j = 0; j < src->cols; j++) {
				 if (src->at<Vec3b>(i, j) == src->at<Vec3b>(y, x)) {
					 if (i < rMin) {
						 rMin = i;
					 }
					 if (i > rMax) {
						 rMax = i;
					 }
					 if (j < cMin) {
						 cMin = j;
					 }
					 if (j > cMax) {
						 cMax = j;
					 }
				 }
			 }
		 }
		 aspectRatio =(float) (cMax - cMin + 1) / (rMax - rMin + 1);
		 printf("Aspect Ratio: %f\n", aspectRatio);
		 // compute aspect ratio

		 // draw elongation axis
		 int rA=0;
		 int rB=0;
		 rA = centerR + tan(angle)*(cMin - centerC);
		 rB = centerR + tan(angle)*(cMax - centerC);
		 Point A(cMin,rA);
		 Point B(cMax,rB);
		 line((*src), A, B, Scalar(0,0,0),2);
		 imshow("line",(*src));
		 // draw elongation axis

		 // the projections on horizontal axis
		 int m = src->rows;
		 int n = src->cols;
		 Mat dstH(m,n,CV_8UC3);
		 for (int i = 0; i < src->rows; i++) {
			 int contor = 0;
			 for (int j = 0; j < src->cols; j++) {
				 if (src->at<Vec3b>(i, j) == src->at<Vec3b>(y, x)) {
					 dstH.at<Vec3b>(i, contor) = src->at<Vec3b>(i, j);
					 contor++;
				 }
			 }
		 }
		 imshow("h", dstH);

		 Mat dstV(m, n, CV_8UC3);
		 for (int j = 0; j < src->cols; j++) {
			 int contor = 0;
			 for (int i = 0; i < src->rows; i++) {
				 if (src->at<Vec3b>(i, j) == src->at<Vec3b>(y, x)) {
					 dstV.at<Vec3b>(src->rows -contor -1,j) = src->at<Vec3b>(i, j);
					 contor++;
				 }
			 }
		 }
		 imshow("v", dstV);
		 // the projections on horizontal and vertical axis


	}
}

void geometrical_features()
{
	Mat src;
	// Read image from file 
	char fname[MAX_PATH];
	while (openFileDlg(fname))
	{
		src = imread(fname);
		//Create a window
		namedWindow("My Window", 1);

		//set the callback function for any mouse event
		setMouseCallback("My Window", geometrical_features_function, &src);

		//show the image
		imshow("My Window", src);

		// Wait until user press some key
		waitKey(0);
	}
}

void bfs_labeling() {

	Mat img = imread("Images/letters.bmp", CV_LOAD_IMAGE_GRAYSCALE);
	int m = img.rows;
	int n = img.cols;

	int label = 0;
	Mat labels(m, n, CV_32SC1,Scalar(0));
	
	Mat dst(m, n,CV_8UC3);

	int offi[9] = { -1,-1,-1,0,0,0,1,1,1 };
	int offj[9] = { -1,0, 1,-1,0,1,-1,0,1 };

	//Mat_<int>h,w,0);
	for (int i = 0; i < m-1; i++) {
		for (int j = 0; j < n-1; j++) {

			if (img.at<uchar>(i, j) == 0 && labels.at<int>(i, j)==0) {
				label++;

				std::queue<Point> Q;
				labels.at<int>(i, j) = label;
				Q.push(Point(j, i));

				while ( !Q.empty() ) {
					Point q = Q.front();
					Q.pop();
					
					for (int k = 0; k < 8; k++) {
						if (q.y + offi[k] > 0 && q.y + offi[k] < m && q.x + offj[k]>0 && q.x + offj[k] < n) {
							if (img.at<uchar>(q.y + offi[k], q.x + offj[k]) == 0 && labels.at<int>(q.y + offi[k], q.x + offj[k]) == 0) {
								labels.at<int>(q.y + offi[k], q.x + offj[k]) = label;
								Q.push(Point(q.x+offj[k], q.y + offi[k]));
							}
						}
					}

				}

			}

		}
	}

	Vec3b colors[100] = { Vec3b(0,0,0) };
	for (int i = 0; i < labels.rows; i++) {
		for (int j = 0; j < labels.cols; j++) {
			int label = labels.at<int>(i, j);
			if (label == 0) {
				dst.at<Vec3b>(i, j) = Vec3b(255, 255, 255);
			}
			else {
				if (colors[label] == Vec3b(0, 0, 0)) {
					colors[label][0] = rand() % 256;
					colors[label][1] = rand() % 256;
					colors[label][2] = rand() % 256;
				}
				dst.at<Vec3b>(i, j) = colors[label];
			}
		}
	}

	imshow("old", img);
	imshow("new", dst);
	waitKey(0);
}

int minElement(std::vector<int> vec) {
	int minL = INT_MAX;
	for (int i = 0; i < vec.size(); i++) {
		minL = min(minL, vec[i]);
	}
	return minL;
}

void twopass_labeling() {

	Mat img = imread("Images/crosses.bmp", CV_LOAD_IMAGE_GRAYSCALE);
	int m = img.rows;
	int n = img.cols;

	int label = 0;
	Mat labels(m, n, CV_32SC1, Scalar(0));

	Mat dst(m, n, CV_8UC3);

	std::vector<std::vector<int>> edges;

	int offi[9] = { -1,-1,-1,0,0,0,1,1,1 };
	int offj[9] = { -1,0, 1,-1,0,1,-1,0,1 };

	for (int i = 0; i < m - 1; i++) {
		for (int j = 0; j < n - 1; j++) {

			if (img.at<uchar>(i, j) == 0 && labels.at<int>(i, j) == 0) {
			
				std::vector<int> L;

				for (int k = 0; k < 8; k++) {
					if(i + offi[k] > 0 && i + offi[k] < m && j + offj[k]>0 && j + offj[k] < n) {
						if (labels.at<int>(i + offi[k], j + offj[k]) > 0) {
							L.push_back(labels.at<int>(i + offi[k], j + offj[k]));
						}
					}
				}

				if (L.size() == 0) {
					label++;
					edges.resize(label + 1);
					labels.at<int>(i, j) = label;
				}
				else {
					int x = minElement(L);
					labels.at<int>(i, j) = x;

					for (int b = 0; b < L.size(); b++) {
						if (L[b] != x) {
							edges[x].push_back(L[b]);
							edges[L[b]].push_back(x);

						}
					}

				}

			}

		}
	}

	int newLabel = 0;		
	std::vector<int> newLabels;
	newLabels.assign(label + 1,0);

	for (int c = 1; c <= label; c++) {
		if (newLabels[c] == 0) {
			newLabel++;
			std::queue<int> Q;
			newLabels[c] = newLabel;
			Q.push(c);
			while (!Q.empty()) {
				int x = Q.front();
				Q.pop();
				for (int d = 0; d < edges[x].size(); d++) {
					if (newLabels[edges[x][d]] == 0) {
						newLabels[edges[x][d]] = newLabel;
						Q.push(edges[x][d]);
					}
				}

			}
		}
	}

	for (int e = 0; e < m-1; e++) {
		for (int f = 0; f < n-1; f++) {
			labels.at<int>(e, f) = newLabels[labels.at<int>(e, f)];
		}
	}

	Vec3b colors[100] = { Vec3b(0,0,0) };
	for (int i = 0; i < labels.rows; i++) {
		for (int j = 0; j < labels.cols; j++) {
			int label = labels.at<int>(i, j);
			if (label == 0) {
				dst.at<Vec3b>(i, j) = Vec3b(255, 255, 255);
			}
			else {
				if (colors[label] == Vec3b(0, 0, 0)) {
					colors[label][0] = rand() % 256;
					colors[label][1] = rand() % 256;
					colors[label][2] = rand() % 256;
				}
				dst.at<Vec3b>(i, j) = colors[label];
			}
		}
	}


	imshow("old", img);
	imshow("new", dst);
	waitKey(0);
}

Point2i getNextPixel(int dir, int i, int j) {
	Point2i nextP;
	switch (dir) {
	case 0: nextP.x = i;
		nextP.y = j + 1;
		break;
	case 1:
		nextP.x = i - 1;
		nextP.y = j + 1;
		break;
	case 2: nextP.x = i - 1;
		nextP.y = j;
		break;
	case 3: nextP.x = i - 1;
		nextP.y = j - 1;
		break;
	case 4: nextP.x = i;
		nextP.y = j - 1;
		break;
	case 5: nextP.x = i + 1;
		nextP.y = j - 1;
		break;
	case 6: nextP.x = i + 1;
		nextP.y = j;
		break;
	case 7: nextP.x = i + 1;
		nextP.y = j + 1;
		break;
	}
	return nextP;
}

void border_tracing() {
	Mat img = imread("Images/skew_ellipse.bmp", CV_LOAD_IMAGE_GRAYSCALE);
	int m = img.rows;
	int n = img.cols;

	int offi[9] = {0,-1,-1,-1,0,1,1,1};
	int offj[9] = {1,1,0,-1,-1,-1,0,1};

	Point pFirst;
	Point pSecond;

	Point pCurrent;
	Point pNext; 

	Mat borderImage(m, n, CV_8UC1);

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (img.at<uchar>(i, j) == 0) {
				pFirst = Point(i, j);
				printf("Starting point is at (%d,%d)", i, j);
				i = m;
				j = n;
			}
		}
	}

	int dir = 7;
	do {
		if (dir % 2 == 0) {
			dir = (dir + 7) % 8;
		}
		else {
			dir = (dir + 6) % 8;
		}
	
		pSecond = Point(pFirst.x + offi[dir], pFirst.y + offj[dir]);
		pCurrent = Point(pSecond.x + offi[dir], pSecond.y + offj[dir]);
		
		while (img.at<uchar>(pCurrent.x, pCurrent.y) != 0) {
			dir = (dir + 1) % 8;
		}
		
		if (img.at<uchar>(pCurrent.x, pCurrent.y) == 0) {

			borderImage.at<uchar>(pCurrent.x, pCurrent.y) = 0;
			pNext = Point(pCurrent.x + offi[dir], pCurrent.y + offj[dir]);
		}

	} while (!(n >= 2 && pFirst == pNext && pCurrent == pFirst));

	imshow("old", img);
	imshow("new", borderImage);
	waitKey(0);

}


void border_tracingL() {
	Mat src;
	// Read image from file 
	char fname[MAX_PATH];
	while (openFileDlg(fname))
	{
		src = imread(fname, CV_LOAD_IMAGE_GRAYSCALE);
		//Create a window
		namedWindow("Objects", 1);

		//show the image
		imshow("Objects", src);

		//border tracing algorithm

		//find start point of object
		Point2i startPoint;
		for (int i = 0; i < src.rows; i++) {
			for (int j = 0; j < src.cols; j++) {
				if (src.at<uchar>(i, j) == 0) {
					startPoint = Point2i(i, j);
					i = src.rows;
					j = src.cols;
				}
			}
		}

		printf("starting point: %d, %d\n", startPoint.x, startPoint.y);
		int dir = 7;
		int n = 1;
		std::vector<Point2i> border;
		std::vector<int> chainCode;
		Point2i currentPoint = startPoint;
		border.push_back(startPoint);
		do {
			if (dir % 2 == 0) {
				dir = (dir + +7) % 8;
			}
			else {
				dir = (dir + 6) % 8;
			}

			Point2i nextP = getNextPixel(dir, currentPoint.x, currentPoint.y);

			//what happens if no neighbors are black?
			while (src.at<uchar>(nextP.x, nextP.y) != 0) {
				dir = (dir + 1) % 8;
				nextP = getNextPixel(dir, currentPoint.x, currentPoint.y);
			}

			if (src.at<uchar>(nextP.x, nextP.y) == 0) {
				border.push_back(nextP);
				n = border.size();
				currentPoint = nextP;
				chainCode.push_back(dir);
			}
		} while (border.size() <= 2 || (border.at(0) != border.at(n - 2) && border.at(1) != border.at(n - 1)));

		//build new image
		Mat borderImg(src.rows, src.cols, CV_8UC1);
		//init with black
		for (int i = 0; i < borderImg.rows; i++) {
			for (int j = 0; j < borderImg.cols; j++) {
				borderImg.at<uchar>(i, j) = 255;
			}
		}
		for (int k = 0; k < border.size(); k++) {
			Point2i p = border.at(k);
			borderImg.at<uchar>(p.x, p.y) = 0;
		}

		printf("Chain code: \n", chainCode.size());
		for (int i = 0; i < chainCode.size(); i++) {
			printf("%d ", chainCode.at(i));
		}

		printf("\n Derivative chain code: \n");
		for (int i = 1; i < chainCode.size(); i++) {
			int val = (chainCode.at(i) - chainCode.at(i - 1) + 8) % 8;
			printf("%d ", val);
		}

		imshow("Border image", borderImg);

		waitKey(0);
	}
}



void reconstruct_image() {
	ifstream f;
	f.open("Images/reconstruct.txt");
	if (!f) {
		cerr << "Unable to open file reconstruct.txt";
		exit(1);   // call system to stop
	}

	int x, y;
	f >> x;
	f >> y;
	Point2i startPoint = Point2i(x, y);
	int nrChainCode;
	f >> nrChainCode;
	std::vector<int> chainCode;
	for (int i = 0; i < nrChainCode; i++) {
		f >> x;
		chainCode.push_back(x);
	}
	f.close();

	Mat img = imread("Images/gray_background.bmp",
		CV_LOAD_IMAGE_GRAYSCALE);
	img.at<uchar>(startPoint.x, startPoint.y) = 0;
	Point2i currentPoint = startPoint;
	for (int k = 0; k < chainCode.size(); k++) {
		int dir = chainCode.at(k);
		Point2i nextP = getNextPixel(dir, currentPoint.x, currentPoint.y);
		img.at<uchar>(currentPoint.x, currentPoint.y) = 0;
		currentPoint = nextP;
	}
	imshow("Newimg", img);
	waitKey(0);
}

void contour_reconstruction() {
	FILE *file;
	file = fopen("D:\\reconstruct.txt", "r");
	
	int pInitialX = 0;
	int pInitialY = 0;
	
	int numberOfChainCodes = 0;

	fscanf(file, "%d %d", &pInitialX, &pInitialY);
	fscanf(file, "%d", &numberOfChainCodes);
	printf("number of %d ", numberOfChainCodes);
	

	waitKey(0);
}

Mat_<uchar> dilatation(Mat_<uchar> img) {
	//Mat_<uchar> img = imread("Images/3_Open/cel4thr3_bw.bmp", CV_LOAD_IMAGE_GRAYSCALE);
	int m = img.rows;
	int n = img.cols;

	Mat_<uchar> dest = img.clone();
	for (int i = 1; i < m-1; i++) {
		for (int j = 1; j < n-1; j++) {
			if (img(i, j) == 0) {
				dest(i - 1, j) = 0;
				dest(i, j - 1) = 0;
				dest(i, j + 1) = 0;
				dest(i + 1, j) = 0;
			}
		}
	}
	
	//imshow("original", img);
	//imshow("dilatation", dest);
	//waitKey(0);

	return dest;
}

void dilatation_ntimes() {
	Mat_<uchar> img = imread("Images/3_Open/cel4thr3_bw.bmp", CV_LOAD_IMAGE_GRAYSCALE);
	
	int number = 0;
	cin >> number;

	Mat_<uchar> dest = img.clone();

	for (int i = 0; i < number; i++) {
		dest = dilatation(dest);
	}

	imshow("original", img);
	imshow("dilatation_ntimes", dest);
	waitKey(0);
}

Mat_<uchar> erosion(Mat_<uchar> img) {
	//Mat_<uchar> img = imread("Images/3_Open/cel4thr3_bw.bmp", CV_LOAD_IMAGE_GRAYSCALE);
	int m = img.rows;
	int n = img.cols;

	Mat_<uchar> dest = img.clone();
	for (int i = 1; i < m - 1; i++) {
		for (int j = 1; j < n - 1; j++) {
			if (img(i-1,j)==255 || img(i,j-1)==255 || img(i,j)==255 || img(i,j+1)==255 || img(i+1,j)==255) {
				dest(i, j) = 255;
			}
		}
	}

	//imshow("original", img);
	//imshow("erosion", dest);
	//waitKey(0);

	return dest;
}

void erosion_ntimes() {
	Mat_<uchar> img = imread("Images/3_Open/cel4thr3_bw.bmp", CV_LOAD_IMAGE_GRAYSCALE);

	int number = 0;
	cin >> number;

	Mat_<uchar> dest = img.clone();

	for (int i = 0; i < number; i++) {
		dest = erosion(dest);
	}

	imshow("original", img);
	imshow("erosion_ntimes", dest);
	waitKey(0);
}


void opening() {
	Mat_<uchar> img = imread("Images/3_Open/cel4thr3_bw.bmp", CV_LOAD_IMAGE_GRAYSCALE);
	int m = img.rows;
	int n = img.cols;

	Mat_<uchar> erosionImg = erosion(img);
	Mat_<uchar> dilatationImg = dilatation(img);

	Mat_<uchar> dest = img.clone();
	dest = erosion(dest);
	dest = dilatation(dest);

	imshow("original", img);
	imshow("erosion", erosionImg);
	imshow("dilatation", dilatationImg);
	imshow("opening", dest);
	waitKey(0);

}

void closing() {
	Mat_<uchar> img = imread("Images/3_Open/cel4thr3_bw.bmp", CV_LOAD_IMAGE_GRAYSCALE);
	int m = img.rows;
	int n = img.cols;

	Mat_<uchar> dest = img.clone();
	dest = dilatation(dest);
	dest = erosion(dest);

	Mat_<uchar> erosionImg = erosion(img);
	Mat_<uchar> dilatationImg = dilatation(img);

	imshow("original", img);
	imshow("erosion", erosionImg);
	imshow("dilatation", dilatationImg);
	imshow("closing", dest);
	waitKey(0);

}

void boundaryExtraction() {
	Mat_<uchar> img = imread("Images/3_Open/cel4thr3_bw.bmp", CV_LOAD_IMAGE_GRAYSCALE);
	int m = img.rows;
	int n = img.cols;

	Mat_<uchar> erosionImg = img.clone();
	Mat_<uchar> boundaryImg = img.clone();
	
	erosionImg = erosion(erosionImg);
	for (int i = 1; i < m - 1; i++) {
		for (int j = 1; j < n - 1; j++) {
			if (img(i, j) == 0 && erosionImg(i, j) == 0) {
				boundaryImg(i, j) = 255;
			}
		}
	}
	
	imshow("original", img);
	imshow("boundary", boundaryImg);
	waitKey(0);

}

Mat_<uchar> intersection(Mat_<uchar> mat1, Mat_<uchar> mat2) {
	Mat_<uchar> intersectionMatrix(mat1.rows, mat1.cols);
	for (int i = 0; i < mat1.rows; i++) {
		for (int j = 0; j <mat1.cols; j++) {
			if (mat1(i, j) == mat2(i, j) && mat1(i, j) == 0) {
				intersectionMatrix(i, j) = 0;
			}
			else {
				intersectionMatrix(i, j) = 255;
			}
		}
	}
	return intersectionMatrix;
}

Mat_<uchar> unionImages(Mat_<uchar> mat1, Mat_<uchar> mat2) {
	Mat_<uchar> unionMatrix(mat1.rows, mat1.cols);
	for (int i = 0; i < mat1.rows; i++) {
		for (int j = 0; j < mat1.cols; j++) {
			if (mat1(i, j) == 0 || mat2(i, j) == 0) {
				unionMatrix(i, j) = 0;
			}
			else {
				unionMatrix(i, j) = 255;
			}
		}
	}
	return unionMatrix;
}

bool areEqual(Mat_<uchar> mat1, Mat_<uchar> mat2) {
	for (int i = 0; i < mat1.rows; i++) {
		for (int j = 0; j < mat1.cols; j++) {
			if (mat1(i, j) != mat2(i, j)) {
				return false;
			}
		}
	}
	return true;
}

void region_filling() {
	Mat_<uchar> img = imread("Images/6_RegionFilling/reg1neg1_bw.bmp", CV_LOAD_IMAGE_GRAYSCALE);
	imshow("Original", img);
	Mat_<uchar> dest(img.rows, img.cols);
	Mat_<uchar> complement;
	complement = (255 - img);

	int initialI = img.rows / 2;
	int initialJ = img.cols / 2;
	printf("Starting region fill at %d %d\n", initialI, initialJ);
	for (int i = 0; i < dest.rows; i++) {
		for (int j = 0; j < dest.cols; j++) {
			dest(i, j) = 255;
		}
	}
	dest(initialI, initialJ) = 0;

	Mat_<uchar> copyNew;
	copyNew = dilatation(dest);
	copyNew = intersection(copyNew, complement);
	int i = 0;
	while (!areEqual(copyNew, dest)) {
		dest = copyNew;
		copyNew = dilatation(dest);
		copyNew = intersection(copyNew, complement);
	}
	dest = unionImages(dest, img);
	imshow("Region Filling", dest);
	waitKey(0);
}


std::vector<int> compute_histogramFunction(Mat *img) {
	std::vector<int> histogram = std::vector<int>(256);
	//initialize vec
	for (int i = 0; i < 256; i++) {
		histogram.at(i) = 0;
	}

	for (int i = 0; i < img->rows; i++) {
		for (int j = 0; j < img->cols; j++) {
			uchar val = img->at<uchar>(i, j);
			histogram.at(val)++;
		}
	}
	return histogram;
}

float compute_mean() {
	Mat_<uchar> imgGS = imread("Images/cameraman.bmp", CV_LOAD_IMAGE_GRAYSCALE);
	int m = imgGS.rows;
	int n = imgGS.cols;

	float mean = 0;

	for (int g = 0; g < 256; g++) {
		mean += g * p[g];
	}
	return mean;
}

float standard_deviation() {
	float std = 0;
	float mean = compute_mean();
	for (int g = 0; g < 256; g++) {
		std += (g - mean)*(g - mean)*p[g];
	}
	return sqrt(std);
}

void basicGlobalThresholding() {

	Mat_<uchar> imgGS = imread("Images/cameraman.bmp", CV_LOAD_IMAGE_GRAYSCALE);
	int m = imgGS.rows;
	int n = imgGS.cols;

	int min = 255;
	int max = 0;

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			uchar value = imgGS(i, j);
			if (value < min) {
				min = value;
			}
			if (value > max) {
				max = value;
			}
		}
	}

	printf("Min val: %d\n", min);
	printf("Max val: %d\n", max);

	float t = (min + max) / 2;
	float t_prev = t;

	float error = 0.1;

	do {
		t = t_prev;
		int n1 = 0;
		float mean1 = 0;
		for (int g = min; g <= t; g++) {
			n1 += h[g];
			mean1 += g * h[g];
		}

		mean1 = mean1 / n1;

		int n2 = 0;
		float mean2 = 0;
		for (int g = t + 1; g <= max; g++) {
			n2 += h[g];
			mean2 += g * h[g];
		}
		mean2 = mean2 / n2;

		t_prev = (mean1 + mean2) / 2;
	} while (abs(t_prev - t) >= error);

	printf("threshold is: %f\n", t_prev);
}

void brightnessChange() {

	Mat_<uchar> imgGS = imread("Images/Hawkes_Bay_NZ.bmp", CV_LOAD_IMAGE_GRAYSCALE);
	int m = imgGS.rows;
	int n = imgGS.cols;

	int offset = 50;

	Mat_<uchar> dest(m, n);

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (imgGS(i, j) + offset > 255) {
				dest(i, j) = 255;
			}
			else if (imgGS(i, j) + offset < 0) {
				dest(i, j) = 0;
			}
			else {
				dest(i, j) = imgGS(i, j) + offset;
			}
		}
	}

	imshow("brightness changed", dest);
	waitKey(0);

}


void contrast_change(int goutmin, int goutmax) {

	histogramComputation();

	Mat_<uchar> imgGS = imread("Images/Hawkes_Bay_NZ.bmp", CV_LOAD_IMAGE_GRAYSCALE);
	int m = imgGS.rows;
	int n = imgGS.cols;

	int ginmin = 0;
	int ginmax = 0;

	for (int i = 0; i < 256; i++) {
		if (h[i] != 0) {
			ginmin = i;
			break;
		}
	}
	for (int i = 255; i >= 0; i--) {
		if (h[i] != 0) {
			ginmax = i;
			break;
		}
	}

	printf("G in min: %d\n", ginmin);
	printf("G in max: %d\n", ginmax);

	Mat_<uchar> dest(m, n);

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {

			int value = imgGS(i, j);
			int gout = goutmin + (value - ginmin) * (goutmax - goutmin) / (ginmax - ginmin);
			if (gout > 255) {
				gout = 255;
			}
			else if (gout < 0) {
				gout = 0;
			}
			dest(i, j) = gout;
		}
	}

	imshow("contrast changed", dest);
	waitKey(0);

}

void gamma_correction(float gamma) {

	histogramComputation();

	Mat_<uchar> imgGS = imread("Images/Hawkes_Bay_NZ.bmp", CV_LOAD_IMAGE_GRAYSCALE);
	int m = imgGS.rows;
	int n = imgGS.cols;

	float L = 255;

	Mat_<uchar> dest(m, n);

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {

			int value = imgGS(i, j);
			int gout = L * pow(value / L, gamma);
			
			if (gout > 255) {
				gout = 255;
			}
			else if (gout < 0) {
				gout = 0;
			}
			dest(i, j) = gout;
		}
	}

	imshow("gamma correction", dest);
	waitKey(0);

}

float *generate_pdf(Mat src) {
	char fname[MAX_PATH];
	int h[256] = { 0 };
	float *pdf = (float*)malloc(256 * sizeof(float));


	Mat imageGray = Mat(src.rows, src.cols, CV_8UC1);
	float M = src.cols * src.rows;

	for (int i = 0; i < src.rows; i++)
		for (int j = 0; j < src.cols; j++) {
			uchar pixel = src.at<uchar>(i, j);
			h[pixel] ++;
		}

	for (int j = 0; j < 256; j++) {
		pdf[j] = (float)h[j] / M;
	}


	return pdf;
}

float histogramPcg(float* pdf, int gray) {
	float s = 0;
	for (int i = 0; i < gray; i++) {
		s += pdf[i];
	}
	return s;
}

void histogramEqualization() {
	Mat src;
	char fname[MAX_PATH];
	double newVal;
	while (openFileDlg(fname)) {
		src = imread(fname, CV_LOAD_IMAGE_GRAYSCALE);
		float *pdf = generate_pdf(src);

		for (int i = 0; i < src.rows; i++)
			for (int j = 0; j < src.cols; j++)
				src.at<uchar>(i, j) = (uchar)(255 * histogramPcg(pdf, src.at<uchar>(i, j)));

		imshow("Histogram equalization", src);
		waitKey();
	}
}

void mean_filter3() {
	Mat img = imread("Images/cameraman.bmp", CV_LOAD_IMAGE_GRAYSCALE);
	Mat dst = img.clone();
	int H[3][3] = { { 1, 1, 1 }, { 1,1,1 }, { 1, 1, 1 } };

	for (int i = 1; i < img.rows - 1; i++) {
		for (int j = 1; j < img.cols - 1; j++) {
			int sum = 0;
			for (int k = 0; k < 3; k++) {
				for (int l = 0; l < 3; l++) {
					sum += img.at<uchar>(i + k - 1, j + l - 1)*H[k][l];
				}
			}
			sum /= 9;
			if (sum > 255) sum = 255;
			if (sum < 0) sum = 0;
			dst.at<uchar>(i, j) = sum;
		}
	}
	imshow("src", img);
	imshow("conv", dst);
	waitKey();
}

void mean_filter5() {
	Mat img = imread("Images/cameraman.bmp", CV_LOAD_IMAGE_GRAYSCALE);
	Mat dst = img.clone();
	int H[5][5] = { { 1, 1, 1 ,1,1}, { 1,1,1,1,1 }, {1,1, 1, 1, 1 },{1,1 ,1, 1, 1 }, {1,1, 1,1,1 } };

	for (int i = 2; i < img.rows - 2; i++) {
		for (int j = 2; j < img.cols - 2; j++) {
			int sum = 0;
			for (int k = 0; k < 5; k++) {
				for (int l = 0; l <5; l++) {
					sum += img.at<uchar>(i + k - 2, j + l - 2)*H[k][l];
				}
			}
			sum /= 25;
			if (sum > 255) sum = 255;
			if (sum < 0) sum = 0;
			dst.at<uchar>(i, j) = sum;
		}
	}
	imshow("src", img);
	imshow("conv", dst);
	waitKey();
}

void gaussian_filter() {
	Mat img = imread("Images/cameraman.bmp", CV_LOAD_IMAGE_GRAYSCALE);
	Mat dst = img.clone();
	int H[3][3] = { { 1,2,1 }, { 2,4,2 }, { 1, 2, 1 } };

	for (int i = 1; i < img.rows - 1; i++) {
		for (int j = 1; j < img.cols - 1; j++) {
			int sum = 0;
			for (int k = 0; k < 3; k++) {
				for (int l = 0; l < 3; l++) {
					sum += img.at<uchar>(i + k - 1, j + l - 1)*H[k][l];
				}
			}
			sum /= 16;
			if (sum > 255) sum = 255;
			if (sum < 0) sum = 0;
			dst.at<uchar>(i, j) = sum;
		}
	}
	imshow("src", img);
	imshow("conv", dst);
	waitKey();
}

void laplace_filter() {
	Mat img = imread("Images/cameraman.bmp", CV_LOAD_IMAGE_GRAYSCALE);
	Mat dst = img.clone();
	int H[3][3] = { { 0,-1,0}, { -1,4,-1 }, {0,-1,0 } };

	for (int i = 1; i < img.rows - 1; i++) {
		for (int j = 1; j < img.cols - 1; j++) {
			int sum = 0;
			for (int k = 0; k < 3; k++) {
				for (int l = 0; l < 3; l++) {
					sum += img.at<uchar>(i + k - 1, j + l - 1)*H[k][l];
				}
			}
			if (sum > 255) sum = 255;
			if (sum < 0) sum = 0;
			dst.at<uchar>(i, j) = sum;
		}
	}
	imshow("src", img);
	imshow("conv", dst);
	waitKey();
}

void highpass_filter() {
	Mat img = imread("Images/cameraman.bmp", CV_LOAD_IMAGE_GRAYSCALE);
	Mat dst = img.clone();
	int H[3][3] = { { 0,-1,0}, { -1,5,-1 }, {0,-1,0 } };

	for (int i = 1; i < img.rows - 1; i++) {
		for (int j = 1; j < img.cols - 1; j++) {
			int sum = 0;
			for (int k = 0; k < 3; k++) {
				for (int l = 0; l < 3; l++) {
					sum += img.at<uchar>(i + k - 1, j + l - 1)*H[k][l];
				}
			}
			if (sum > 255) sum = 255;
			if (sum < 0) sum = 0;
			dst.at<uchar>(i, j) = sum;
		}
	}
	imshow("src", img);
	imshow("conv", dst);
	waitKey();
}

void centering_transform(Mat img) {
	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			img.at<float>(i, j) = ((i + j) & 1) ? -img.at<float>(i, j) : img.at<float>(i, j);
		}
	}
}

Mat generic_frequency_domain_filter(Mat src) {
	//convert input image to float image
	Mat srcf;
	src.convertTo(srcf, CV_32FC1);
	//centering transformation
	centering_transform(srcf);
	//perform forward transform with complex image output
	Mat fourier;
	dft(srcf, fourier, DFT_COMPLEX_OUTPUT);
	//split into real and imaginary channels
	Mat channels[] = { Mat::zeros(src.size(),CV_32F), Mat::zeros(src.size(),CV_32F) };
	split(fourier, channels);
	//calculate magnitude and phase in floating point images mag and phi
	Mat mag, phi;
	magnitude(channels[0], channels[1], mag);
	phase(channels[0], channels[1], phi);
	//display the phase and magnitude image here

	for (int i = 0; i < mag.rows; i++) {
		for (int j = 0; j < mag.cols; j++) {
			mag.at<float>(i, j) = log(1+mag.at<float>(i, j));
		}
	}
	normalize(mag,mag,0,255, NORM_MINMAX, CV_8UC1);
	for (int i = 0; i < phi.rows; i++) {
		for (int j = 0; j < phi.cols; j++) {
			phi.at<float>(i, j) = log(1+phi.at<float>(i, j));
		}
	}
	normalize(phi, phi, 0, 255, NORM_MINMAX, CV_8UC1);

	imshow("magn", mag);
	imshow("phase",phi);
	
	//insert filtering operations on fourier coefficients here

	/*mag = lowPassFourier(mag,10);
	imshow("m",mag);*/
	/*	mag = highPassFourier(mag, 10);
		imshow("m",mag);

		*/
		//store in real part in channels[0] and imaginary part in channels[1]


		//perform inverse transform and put results in dsft
	Mat dst, dstf;
	merge(channels, 2, fourier);
	dft(fourier, dstf, DFT_INVERSE | DFT_REAL_OUTPUT | DFT_SCALE);

	//inverse centering transformation
	centering_transform(dstf);

	//normalize the result and put in the destinaiton image
	normalize(dstf, dst, 0, 255, NORM_MINMAX, CV_8UC1);
	waitKey();

	return dst;
}

Mat magnitude_log_fourier_centered_spectrum(Mat src) {
	Mat srcf;
	src.convertTo(srcf, CV_32FC1);
	
	centering_transform(srcf);

	Mat fourier;
	dft(srcf, fourier, DFT_COMPLEX_OUTPUT);

	Mat channels[] = { Mat::zeros(src.size(),CV_32F),Mat::zeros(src.size(),CV_32F) };
	split(fourier, channels);

	Mat mag, phi;
	magnitude(channels[0], channels[1], mag);
	phase(channels[0], channels[1], phi);

	/*for (int i = 0; i < mag.rows; i++) {
		for (int j = 0; j < mag.cols; j++) {
			mag.at<float>(i, j) = log(1+mag.at<float>(i, j));
		}
	}*/

	// insert filtering operations here

	// to redo 
	for (int i = 0; i < mag.rows; i++) {
		for (int j = 0; j < mag.cols; j++) {
			float raza = 10;
			float result = (mag.rows / 2 - i)*(mag.rows / 2 - i) + (mag.cols / 2 - j)*(mag.cols / 2 - j);
			if (result < raza*raza) {
				channels[0].at<float>(i, j) = channels[0].at<float>(i,j);
				channels[1].at<float>(i, j) = channels[1].at<float>(i, j);
			}
			else {
				channels[0].at<float>(i, j) = 0;
				channels[1].at<float>(i, j) = 0;
			}
		}
	}

	Mat dst,dstf;
	merge(channels, 2, fourier);
	dft(fourier, dstf, DFT_INVERSE | DFT_REAL_OUTPUT | DFT_SCALE);

	centering_transform(dstf);

	normalize(dstf, dst, 0, 255, NORM_MINMAX, CV_8UC1);

	imshow("mag", dstf);
	waitKey();
	return dstf;
}

void ideal_cut_lowpass_filter() {

		Mat src = imread("Images/cameraman.bmp", CV_LOAD_IMAGE_GRAYSCALE);
		Mat srcf;
		src.convertTo(srcf, CV_32FC1);

		centering_transform(srcf);

		Mat fourier;
		dft(srcf, fourier, DFT_COMPLEX_OUTPUT);

		Mat channels[] = { Mat::zeros(src.size(), CV_32F), Mat::zeros(src.size(), CV_32F) };
		split(fourier, channels);

		Mat mag, phi;
		magnitude(channels[0], channels[1], mag);
		phase(channels[0], channels[1], phi);


		// insert filtering operaitons on Fourier coefficient here
		int height = mag.rows;
		int width = mag.cols;

		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
				if (((i - height / 2)*(i - height / 2) + (j - width / 2)*(j - width / 2)) > 100) {
					channels[0].at<float>(i, j) = 0;
					channels[1].at<float>(i, j) = 0;
				}

		Mat dst, dstf;
		merge(channels, 2, fourier);
		dft(fourier, dstf, DFT_INVERSE | DFT_REAL_OUTPUT | DFT_SCALE);

		centering_transform(dstf);

		normalize(dstf, dst, 0, 255, NORM_MINMAX, CV_8UC1);

		imshow("Magnitude", dst);
		waitKey();
	
}

void ideal_cut_highpass_filter() {

		Mat src = imread("Images/cameraman.bmp", CV_LOAD_IMAGE_GRAYSCALE);

		Mat srcf;
		src.convertTo(srcf, CV_32FC1);

		centering_transform(srcf);

		Mat fourier;
		dft(srcf, fourier, DFT_COMPLEX_OUTPUT);

		Mat channels[] = { Mat::zeros(src.size(), CV_32F), Mat::zeros(src.size(), CV_32F) };
		split(fourier, channels);

		Mat mag, phi;
		magnitude(channels[0], channels[1], mag);
		phase(channels[0], channels[1], phi);


		// insert filtering operaitons on Fourier coefficient here
		int height = mag.rows;
		int width = mag.cols;

		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
				if (((i - height / 2)*(i - height / 2) + (j - width / 2)*(j - width / 2)) <= 100) {
					channels[0].at<float>(i, j) = 0;
					channels[1].at<float>(i, j) = 0;
				}

		Mat dst, dstf;
		merge(channels, 2, fourier);
		dft(fourier, dstf, DFT_INVERSE | DFT_REAL_OUTPUT | DFT_SCALE);

		centering_transform(dstf);

		normalize(dstf, dst, 0, 255, NORM_MINMAX, CV_8UC1);

		imshow("Magnitude", dst);
		waitKey();

}

void gaussian_cut_lowpass_filter() {
		Mat src = imread("Images/cameraman.bmp", CV_LOAD_IMAGE_GRAYSCALE);
	
		Mat srcf;
		src.convertTo(srcf, CV_32FC1);

		centering_transform(srcf);

		Mat fourier;
		dft(srcf, fourier, DFT_COMPLEX_OUTPUT);

		Mat channels[] = { Mat::zeros(src.size(), CV_32F), Mat::zeros(src.size(), CV_32F) };
		split(fourier, channels);

		Mat mag, phi;
		magnitude(channels[0], channels[1], mag);
		phase(channels[0], channels[1], phi);

		int height = mag.rows;
		int width = mag.cols;

		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++) {
				channels[0].at<float>(i, j) = channels[0].at<float>(i, j) *exp(-(((i - height / 2)*(i - height / 2) + (j - width / 2)*(j - width / 2)) / 100.0));
				channels[1].at<float>(i, j) = channels[1].at<float>(i, j) *exp(-(((i - height / 2)*(i - height / 2) + (j - width / 2)*(j - width / 2)) / 100.0));
			}

		Mat dst, dstf;
		merge(channels, 2, fourier);
		dft(fourier, dstf, DFT_INVERSE | DFT_REAL_OUTPUT | DFT_SCALE);

		centering_transform(dstf);

		normalize(dstf, dst, 0, 255, NORM_MINMAX, CV_8UC1);

		imshow("Magnitude", dst);
		waitKey();
	
}

void gaussian_cut_highpass_filter() {
	Mat src = imread("Images/cameraman.bmp", CV_LOAD_IMAGE_GRAYSCALE);

	Mat srcf;
	src.convertTo(srcf, CV_32FC1);

	centering_transform(srcf);

	Mat fourier;
	dft(srcf, fourier, DFT_COMPLEX_OUTPUT);

	Mat channels[] = { Mat::zeros(src.size(), CV_32F), Mat::zeros(src.size(), CV_32F) };
	split(fourier, channels);

	Mat mag, phi;
	magnitude(channels[0], channels[1], mag);
	phase(channels[0], channels[1], phi);

	int height = mag.rows;
	int width = mag.cols;

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++) {
			channels[0].at<float>(i, j) = channels[0].at<float>(i, j) *(1-exp(-(((i - height / 2)*(i - height / 2) + (j - width / 2)*(j - width / 2)) / 100.0)));
			channels[1].at<float>(i, j) = channels[1].at<float>(i, j) *(1-exp(-(((i - height / 2)*(i - height / 2) + (j - width / 2)*(j - width / 2)) / 100.0)));
		}

	Mat dst, dstf;
	merge(channels, 2, fourier);
	dft(fourier, dstf, DFT_INVERSE | DFT_REAL_OUTPUT | DFT_SCALE);

	centering_transform(dstf);

	normalize(dstf, dst, 0, 255, NORM_MINMAX, CV_8UC1);

	imshow("Magnitude", dst);
	waitKey();

}

void median_filter(int w) {
	Mat img = imread("Images/balloons_Salt&Pepper.bmp", CV_LOAD_IMAGE_GRAYSCALE);

	Mat dst = img.clone();

	int m = img.rows;
	int n = img.cols;

	vector<int> v;

	for (int i = 1; i < m-1; i++) {
		for (int j = 1; j < n-1; j++) {
			v.clear();

			for (int k = -w/2; k <= w/2; k++) {
				for (int l = -w/2; l <= w/2; l++) {
					v.push_back(img.at<uchar>(i + k, j + l));
				}
			 }

			std::sort(v.begin(), v.end());

			dst.at<uchar>(i, j) = v[4];
		}
	}

	imshow("img", img);
	imshow("dst", dst);
	waitKey(0);
}

void gaussian_filter2D_kernel() {

	//kernel
	Mat kernel(5, 5, CV_32FC1);

	int w = 5;

	float sigma = 0.8;

	for (int i = 0; i < w; i++) {
		for (int j = 0; j < w; j++) {
			float expr = -( (i-w/2)*(i-w/2) + (j-w/2)*(j-w/2)) / (2 * sigma*sigma);
			kernel.at<float>(i, j) = 1 / (2.0*PI*sigma*sigma) * exp(expr);
		}
	}

	Mat img = imread("Images/balloons_Gauss.bmp", CV_8UC1);

	// convolution
	Mat dst(img.rows, img.cols, CV_8UC1);
	int k = kernel.rows / 2;
	for (int i = k; i < img.rows - k; i++) {
		for (int j = k; j < img.cols - k; j++) {
			int sum = 0;
			for (int x = 0; x < kernel.rows ; x++) {
				for (int y = 0; y < kernel.cols ; y++) {
					sum += img.at<uchar>(i + x - k, j + y - k)*kernel.at<float>(x, y);
				}
			}
			if (sum < 0) sum = 0;
			if (sum > 255) sum = 255;
			dst.at<uchar>(i, j) = sum;
		}
	}

	imshow("src", img);
	imshow("conv", dst);
	waitKey();

}

void gaussian_filter1D_kernel() {
	Mat img = imread("Images/balloons_Gauss.bmp", CV_LOAD_IMAGE_GRAYSCALE);
	Mat dst = img.clone();
	Mat final = img.clone();

	int w = 5;
	
	//kernels
	float gx[5];
	float gy[5];

	float sigma = 0.8;

	for (int i = 0; i < w; i++) {
		float expr = -(((i - w / 2)*(i - w / 2)) / (2.0*sigma*sigma));
		gx[i] = ( 1 / ( (sqrt(2.0*PI)) * sigma)) * exp(expr);
		gy[i] = ( 1 / ( (sqrt(2.0*PI)) * sigma)) * exp(expr);
	}
	
	int k = w / 2;
	for (int i = k; i < img.rows - k; i++) {
		for (int j = k; j < img.cols - k; j++) {
			int sum = 0;
			for (int x = 0; x < w; x++) {
				//for (int y = 0; y < w; y++) {
				sum += img.at<uchar>(i + x - k, j /*+ y*/ - k)*gx[x];// *gy[y];
				//}
			}

			dst.at<uchar>(i, j) = sum;
		}
	}

	for (int i = k; i < img.rows - k; i++) {
		for (int j = k; j < img.cols - k; j++) {
			int sum = 0;
			//for (int x = 0; x < w; x++) {
				for (int y = 0; y < w; y++) {
					sum += dst.at<uchar>(i /*+ x*/ - k, j + y - k)*gy[y];// *gy[y];
				}
		//	}

			final.at<uchar>(i, j) = sum;
		}
	}

	imshow("src", img);
	imshow("dst", final);
	waitKey();
}

int checkPoint(float orientation) {
	if ((orientation <= (PI / 8) && orientation >= ((-PI) / 8))  || (orientation>= (7*PI/8) && orientation<= ((-7*PI)/8))) {
		return 0;
	}
	else if ((orientation <= ((3*PI) / 8) && orientation >= ((PI) / 8)) || (orientation <= ((-5) * PI / 8) && orientation >= ((-7 * PI) / 8))) {
		return 1;
	}
	else if ((orientation <= ((5*PI) / 8) && orientation >= ((3*PI) / 8)) || (orientation <= ((-3) * PI / 8) && orientation >= ((-5 * PI) / 8))) {
		return 2;
	} 
	else {
		return 3;
	}

}

void canny_edge_detection() {
	
	Mat src = imread("Images/saturn.bmp", CV_LOAD_IMAGE_GRAYSCALE);
	
	Mat gradientX = Mat(src.rows, src.cols, CV_32FC1);
	Mat gradientY = Mat(src.rows, src.cols, CV_32FC1);
	
	Mat gradient = Mat(src.rows, src.cols, CV_32FC1);
	Mat magnitude = src.clone();
	Mat maxima = src.clone();

	Mat orientation = Mat(src.rows, src.cols, CV_32FC1);

	int Gx[3][3] = { {-1,0,1},{-2,0,2},{-1,0,1} };
	int Gy[3][3] = { {1,2,1},{0,0,0},{-1,-2,-1} };

	for (int i = 1; i < src.rows-1; i++) {
		for (int j = 1; j < src.cols-1; j++) {
			int sumX = 0;
			int sumY = 0;
			
			for (int k = 0; k < 3; k++) {
				for (int l = 0; l < 3; l++) {
					sumX += src.at<uchar>(i + k - 1, j + l - 1)*Gx[k][l];
					sumY += src.at<uchar>(i + k - 1, j + l - 1)*Gy[k][l];
				}
			}

			gradientX.at<int>(i, j) = sumX;
			gradientY.at<int>(i, j) = sumY;

		}
	}

	for (int i = 0; i < src.rows; i++) {
		for (int j = 0; j < src.cols; j++) {
			orientation.at<float>(i, j) = atan2(gradientY.at<int>(i, j),gradientX.at<int>(i, j));
		}
	}

	for (int i = 0; i < src.rows; i++) {
		for (int j = 0; j < src.cols; j++) {
			gradient.at<float>(i, j) = sqrt(gradientX.at<int>(i, j)*gradientX.at<int>(i, j) + gradientY.at<int>(i, j)*gradientY.at<int>(i, j)) / (4 * sqrt(2));
		}
	}

	// conversie din float in uchar
	for (int i = 0; i < src.rows; i++) {
		for (int j = 0; j < src.cols; j++) {
			magnitude.at<uchar>(i, j) = (uchar)gradient.at<float>(i, j);
		}
	}

	Mat supp = gradient.clone();
	for (int i = 1; i < supp.rows - 1; i++) {
		for (int j = 1; j < supp.cols - 1; j++) {
			float fi = orientation.at<float>(i, j);
			int cadran = checkPoint(fi);

			if (cadran == 0) {
				if (supp.at<float>(i, j) < supp.at<float>(i, j - 1) || supp.at<float>(i, j) < supp.at<float>(i, j + 1)) {
					supp.at<float>(i, j) = 0;
				}
			}
			else if (cadran == 1) {
				if (supp.at<float>(i, j) < supp.at<float>(i-1, j+ 1) || supp.at<float>(i, j) < supp.at<float>(i+1, j- 1)) {
					supp.at<float>(i, j) = 0;
				}
			} 
			else if (cadran == 2) {
				if (supp.at<float>(i, j) < supp.at<float>(i - 1, j) || supp.at<float>(i, j) < supp.at<float>(i + 1, j)) {
					supp.at<float>(i, j) = 0;
				}
			}
			else if (cadran == 3) {
				if (supp.at<float>(i, j) < supp.at<float>(i-1, j-1 ) || supp.at<float>(i, j) < supp.at<float>(i+1, j+1 )) {
					supp.at<float>(i, j) = 0;
				}
			}
		}
	}

	// conversie din float in uchar
	for (int i = 0; i < src.rows; i++) {
		for (int j = 0; j < src.cols; j++) {
			maxima.at<uchar>(i, j) = (uchar)supp.at<float>(i, j);
		}
	}

	// lab 12
	float p = 0.1;
	int histogram[256] = { 0 };
	for (int i = 1; i < src.rows-1; i++) {
		for (int j = 1; j < src.cols-1; j++) {
			histogram[maxima.at<uchar>(i, j)]++;
		}
	}
	int NoEdgePixels = p * ((src.cols - 2)*(src.rows - 2) - histogram[0]);

	printf(" histogram[0] = %d \n", histogram[0]);
	printf("%d", NoEdgePixels);

	int sum = 0;
	int threshold = 0;

	for (int i = 255; i > 0; i--) {
		sum += histogram[i];
		if (sum > NoEdgePixels) {
			threshold= i;
			printf("sum = %d\n", sum);
			break;
		}
	}

	float thresholdHigh = (float)threshold;
	float k = 0.4;
	float thresholdLow = k * threshold;

	printf("threshold = %d", threshold);

	Mat addaptiveMat = maxima.clone();
	for (int i = 1; i < src.rows - 1; i++) {
		for (int j = 1; j < src.cols - 1; j++) {
			if (maxima.at<uchar>(i, j) < thresholdLow) {
				addaptiveMat.at<uchar>(i, j) = 0;
			}
			else if (maxima.at<uchar>(i, j) > thresholdHigh) {
				addaptiveMat.at<uchar>(i, j) = 255;
			}
			else {
				addaptiveMat.at<uchar>(i, j) = 127;
			}
		}
	}

	int di[8] = { -1,-1,-1, 0, 0, 1,1,1 };
	int dj[8] = { -1, 0, 1, -1,1, -1,0,1 };

	for (int i = 1; i < src.rows-1; i++) {
		for (int j = 1; j < src.cols-1; j++) {
			if (addaptiveMat.at<uchar>(i, j) == 255) {

				std::queue<Point2i> Q;
				Q.push(Point2i(j,i));

				while (!Q.empty()) {
					Point2i p = Q.front();
					Q.pop();

					for (int k = 0; k < 8; k++) {
						if (addaptiveMat.at<uchar>(p.y + di[k], p.x + dj[k]) == 127) {
							Q.push(Point2i(p.x + dj[k], p.y + di[k]));

							addaptiveMat.at<uchar>(p.y + di[k], p.x + dj[k]) = 255;
						}
					}

				}

			}
		}
	}

	for (int k = 1; k < addaptiveMat.rows - 1; k++) {
		for (int l = 1; l < addaptiveMat.cols - 1; l++) {
			if (addaptiveMat.at<uchar>(k, l) == 127) {
				addaptiveMat.at<uchar>(k, l) = 0;
			}
		}
	}

	//imshow("src", src);
	//imshow("gradient",magnitude);
	//imshow("supp",maxima);
	imshow("addaptiveMat", addaptiveMat);

	waitKey();
}
	
// CTRL + M + O - to collapse all
int main()
{ 
	int op;
	do
	{
		//system("cls");
		destroyAllWindows();
		printf("Menu:\n");
		printf(" 1 - Open image\n");
		printf(" 2 - Open BMP images from folder\n");
		printf(" 3 - Image negative - diblook style\n");
		printf(" 4 - BGR->HSV\n");
		printf(" 5 - Resize image\n");
		printf(" 6 - Canny edge detection\n");
		printf(" 7 - Edges in a video sequence\n");
		printf(" 8 - Snap frame from live video\n");
		printf(" 9 - Mouse callback demo\n");
		printf(" 10 - Negative Image\n");
		printf(" 11 - Additive Gray Scale Image\n");
		printf(" 12 - Multiplicative Gray Scale Image\n");
		printf(" 13 - Split Image\n");
		printf(" 14 - Inverse Matrix\n");
		printf(" 15 - Rotate Image\n");
		printf(" 16 - RGBChannels\n");
		printf(" 17 - RGBtoGrayScale\n");
		printf(" 18 - GrayScaleToBW\n");
		printf(" 19 - RGBtoHSV\n");
		printf(" 20 - isInside\n");
		printf(" 21 - histogramComputation\n");
		printf(" 22 - multilevelThresholding\n");
		printf(" 23 - floyd\n");
		printf(" 24 - geometrical_Features\n");
		printf(" 25 - bfs_labeling\n");
		printf(" 26 - twopass_labeling\n");
		printf(" 27 - border_tracing\n");
		printf(" 28 - contour_reconstruction\n");
		printf(" 29 - dilatation\n");
		printf(" 30 - dilatation_ntimes\n");
		printf(" 31 - erosion\n");
		printf(" 32 - erosion_ntimes\n");
		printf(" 33 - opening\n");
		printf(" 34 - closing\n");
		printf(" 35 - boundaryExtraction\n");
		printf(" 36 - region_filling\n");
		printf(" 37 - compute_mean_and_std\n");
		printf(" 38 - basicGlobalThresholding\n");
		printf(" 39 - brightnessChange\n");
		printf(" 40 - contrast_change\n");
		printf(" 41 - gamma_correction\n");
		printf(" 42 - mean_filter3\n");
		printf(" 43 - mean_filter5\n");
		printf(" 44 - gaussian_filter\n");
		printf(" 45 - laplace_filter\n");
		printf(" 46 - highpass_filter\n");
		printf(" 47 - magnitude_log_fourier_centered_spectrum\n");
		printf(" 48 - ideal_cut_lowpass_filter\n");
		printf(" 49 - ideal_cut_highpass_filter\n");
		printf(" 50 - gaussian_cut_lowpass_filter\n");
		printf(" 51 - gaussian_cut_highpass_filter\n");
		printf(" 52 - median_filter\n");
		printf(" 53 - gaussian_filter2D_kernel\n");
		printf(" 54 - gaussian_filter1D_kernel\n");
		printf(" 55 - canny_edge_detection\n");
		printf(" 0 - Exit\n\n");
		printf("Option: ");
		scanf("%d",&op);

		Mat_<uchar> img = imread("Images/3_Open/cel4thr3_bw.bmp", CV_LOAD_IMAGE_GRAYSCALE);

		switch (op)
		{
		case 1:
			testOpenImage();
			break;
		case 2:
			testOpenImagesFld();
			break;
		case 3:
			testParcurgereSimplaDiblookStyle(); //diblook style
			break;
		case 4:
			//testColor2Gray();
			testBGR2HSV();
			break;
		case 5:
			testResize();
			break;
		case 6:
			testCanny();
			break;
		case 7:
			testVideoSequence();
			break;
		case 8:
			testSnap();
			break;
		case 9:
			testMouseClick();
			break;
		case 10:
			negative_image();
			break;
		case 11:
			change_gray_levels_additive();
			break;
		case 12:
			change_gray_levels_multiplicative();
			break;
		case 13:
			split_image();
			break;
		case 14:
			inverse_matrix();
			break;
		case 15:
			rotate_image();
			break;
		case 16:
			RGBChannels();
			break;
		case 17:
			RGBtoGrayScale();
			break;
		case 18:
			GrayScaleToBW();
			break;
		case 19:
			RGBtoHSV();
			break;
		case 20:
			int i, j;
			scanf("%d", &i);
			scanf("%d", &j);
			char fname[MAX_PATH];
			while (openFileDlg(fname)) {
				Mat_<Vec3b> img = imread(fname);
				if (isInside(img, i, j)) {
					printf("Inside");
				}
				else {
					printf("Not inside");
				}
			}

			break;
		case 21:
			histogramComputation();
			showHistogram("Histogram", h, 256, 500);
			break;
		case 22:
			histogramComputation();
			multilevelThresholding();
			break;
		case 23:
			histogramComputation();
			floyd();
			break;
		case 24:
			geometrical_features();
			break;
		case 25:
			bfs_labeling();
			break;
		case 26:
			twopass_labeling();
			break;
		case 27:
			border_tracingL();
			break;
		case 28:
			reconstruct_image();
			break;
		case 29:
			dilatation(img);
			break;
		case 30:
			dilatation_ntimes();
			break;
		case 31:
			erosion(img);
			break;
		case 32:
			erosion_ntimes();
			break;
		case 33:
			opening();
			break;
		case 34:
			closing();
			break;
		case 35:
			boundaryExtraction();
			break;
		case 36:
			region_filling();
			break;
		case 37: {
			histogramComputation();
			float mean = compute_mean();
			float stddev = standard_deviation();
			printf("Mean Value = %f\n", mean);
			printf("Standard Deviation Value = %f\n", stddev);
			getchar(); // ca sa nu inchid consola
			getchar(); }
				 break;
		case 38:
			histogramComputation();
			basicGlobalThresholding();
			getchar();
			getchar();
			break;
		case 39:
			brightnessChange();
			break;
		case 40:
			contrast_change(10, 250);
			break;
		case 41:
			//gamma_correction(10);
			histogramEqualization();
			break;
		case 42:
			mean_filter3();
			break;
		case 43:
			mean_filter5();
			break;
		case 44:
			gaussian_filter();
			break;
		case 45:
			laplace_filter();
			break;
		case 46:
			highpass_filter();
			break;
		case 47: {
			Mat src = imread("Images/cameraman.bmp", CV_LOAD_IMAGE_GRAYSCALE);
			magnitude_log_fourier_centered_spectrum(src); }
				 break;
		case 48:
			ideal_cut_lowpass_filter();
			break;
		case 49:
			ideal_cut_highpass_filter();
			break;
		case 50:
			gaussian_cut_lowpass_filter();
			break;
		case 51:
			gaussian_cut_highpass_filter();
			break;
		case 52:
			median_filter(3);
			break;
		case 53:
			gaussian_filter2D_kernel();
			break;
		case 54:
			gaussian_filter1D_kernel();
			break;
		case 55:
			canny_edge_detection();
			break;
		}
	}
	while (op!=0);
	return 0;
}