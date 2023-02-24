#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

/*
	����:
	 C:\Users\User\Desktop\�v���B�z\hw3\Assignment3\fig.jpg
	 C:\Users\User\Pictures\Saved Pictures\A.jpg
*/

int main()
{

	while (true)
	{
		string path = "";
		Mat original;
		Mat src;
		Mat img;
		cout << "\n�п�J�Ϥ����|(�Y�n�h�X,�h��J0): ";

		getline(cin, path);
		if (path == "0")
			break;

		original = imread(path, IMREAD_COLOR);  // ���
		src = imread(path, IMREAD_GRAYSCALE);  // �N�Ϲ��H�Ƕ��Ϫ��覡Ū��

		if (src.empty())
		{
			cout << "\n�Ϥ������|���~\n";
			continue;
		}

		GaussianBlur(src, img, Size(3, 3), 0, 0, BORDER_DEFAULT);  // �����ҽk���\��: �N�Ӥ������T�h���A�����ڭ̧����Ǫ�����

		Mat grad_x, grad_y;
		Mat abs_grad_x, abs_grad_y;
		Mat output;
		Mat edges_Image;

		// Sobel �D�n�Ω���t����(�u��@�Ω�Ƕ���)
		Sobel(img, grad_x, CV_64F, 1, 0,3);  // �� x ��V�p���סA�Ҳ��ͪ���
		Sobel(img, grad_y, CV_64F, 0, 1, 3); // �� y ��V�p���סA�Ҳ��ͪ���
		convertScaleAbs(grad_x, abs_grad_x);  //  convertScaleAbs �Ω�N�Ϥ��W�j
		convertScaleAbs(grad_y, abs_grad_y);
		addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, edges_Image);   // �N grad_x �M grad_y ���� �ĦX�b�@�_


		const int EDGES_THRESHOLD = 65;  // �]�w�H��
		const int max = 255;																			// THRESH_BINARY_INV  => �O�@�� �Ϲ��G�Ȥƪ��W�h
		threshold(edges_Image, output, EDGES_THRESHOLD, max, THRESH_BINARY_INV);  // threshold��ơA�����Ϥ����ܶ� or ���ܥ�(�N�Ϲ��W�������I���ǫ׭ȡA�]�m��0��255)

		namedWindow("���", WINDOW_AUTOSIZE);
		namedWindow("�Ƕ���(�����ҽk�B�z�L)", WINDOW_AUTOSIZE);
		namedWindow("��t��������", WINDOW_AUTOSIZE);  
		namedWindow("���y��", WINDOW_AUTOSIZE);

		imshow("���", original);
		imshow("�Ƕ���(�����ҽk�B�z�L)", img);
		imshow("��t��������", edges_Image);
		imshow("���y��", output);

		waitKey(0);  

		destroyWindow("���");
		destroyWindow("�Ƕ���(�����ҽk�B�z�L)");
		destroyWindow("��t��������");
		destroyWindow("���y��");

		cin.clear(); 

	 }

}