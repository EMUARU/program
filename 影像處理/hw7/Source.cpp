#include<opencv2/opencv.hpp>
#include<iostream>
#define PI 3.1415926

using namespace cv;
using namespace std;

/*
	����:
	 C:\Users\User\Desktop\�v���B�z\hw7\Assignment7\IMG_5702.JPG
	 C:\Users\User\Desktop\�v���B�z\hw7\Assignment7\IMG_5703.JPG
	 C:\Users\User\Desktop\�v���B�z\hw7\Assignment7\IMG_5704.JPG
*/

int main()
{

	while (true)
	{
		string path = "";
		Mat img,original;
		cout << "\n�п�J�Ϥ����|(�Y�n�h�X,�h��J0): ";

		getline(cin, path);
		if (path == "0")
			break;


		img = imread(path, IMREAD_GRAYSCALE); 
		original = imread(path);

		if (img.empty())
		{
			cout << "\n�Ϥ������|���~\n";
			continue;
		}

		resize(img, img, Size(), 0.1, 0.1);
		resize(original, original, Size(), 0.1, 0.1);

		Mat BinaryImage, result;

		threshold(img, BinaryImage, 35, 255, THRESH_BINARY);  //�Ϥ��G�Ȥ�

		erode(BinaryImage, result, Mat());  // erode �u��Ω�g�L�G�ȤƹB�⪺�Ƕ��Ϥ�
		dilate(result, result, Mat()); // dilate �u��Ω�g�L�G�ȤƹB�⪺�Ƕ��Ϥ�

		vector<Vec3f> circles;
		HoughCircles(result, circles,HOUGH_GRADIENT, 1, 20, 100, 8, 15, 24);  //�����ϤW�����

		for (size_t i = 0; i < circles.size(); i++)
		{
			Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));  //��X���
			int radius = cvRound(circles[i][2]);	// ��X�ꪺ�b�|
			circle(original, center, radius, Scalar(155, 50, 255), 3, 8, 0);  // �ھڶ�ߤΥb�| �e��
		}

		cout <<"\n����`��: " << circles.size() << endl;

		namedWindow("�g�L�v���I�k�ο��Ȫ���", WINDOW_AUTOSIZE);
		namedWindow("���������G", WINDOW_AUTOSIZE);
		
		imshow("�g�L�v���I�k�ο��Ȫ���", result);
		imshow("���������G", original);
		waitKey(0);

		destroyWindow("�g�L�v���I�k�ο��Ȫ���");
		destroyWindow("���������G");
		cin.clear();

	}

}