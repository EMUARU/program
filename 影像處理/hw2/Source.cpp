#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

/*
	����:
		C:\Users\User\Pictures\Saved Pictures\A.jpg
		C:\Users\User\Desktop\�v���B�z\hw2\Assignment2\yzu.bmp
*/


int height;  // �Ϥ�������
int width;  // �Ϥ����e��
int angle; // ���� �u�����i�Ϥ����ϡv������
int angle2; // ���� �u���त�����ꪺ�ϡv������
int MaxAngle = 359;
double radius;  // ��Ϊ��b�|
 

Point center;
Mat image;
Mat image2;
Mat image3;
Mat rotated_image; // �s �u�����i�Ϥ����ϡv

static void on_trackbar1(int, void*)  // ���� �u�����i�Ϥ����ϡv
{

	Mat rotation_matix = getRotationMatrix2D(center, angle, 1.0);  // �ϥΦ��禡�o�����x�}(�H�Ϥ������߰�����,�ĤT�ӰѼƥN��Ϥ�����j���v)
	
	warpAffine(image, rotated_image, rotation_matix, image.size());  // �Q�α���x�}�A����Ϥ�

	imshow("�����i�Ϥ�����", rotated_image);

}

static void on_trackbar2(int, void*)  // ���� �u���त�����ꪺ�ϡv
{

	Mat rotation_matix = getRotationMatrix2D(center, angle2, 1.0);  // �ϥΦ��禡�o�����x�}(�H�Ϥ������߰�����,�ĤT�ӰѼƥN��Ϥ�����j���v)
	Mat image4;  // �s �u���৹�᪺��v
	warpAffine(image2, image4, rotation_matix, image.size());  // �Q�α���x�}�A�N��ΰ�����A�A�s�� image4

	for (int x = 0; x < width; x++)  // �N �u���৹�᪺��v �P �u���Χ��Ϥ���A�ѤU���I���v���X��
		for (int y = 0; y < height; y++)
		{
			int temp = (x - center.x) * (x - center.x) + (y - center.y) * (y - center.y);

			if (temp < (radius * radius))
			{
				image3.at<Vec3b>(Point(x, y))[0] = image4.at<Vec3b>(Point(x, y))[0];
				image3.at<Vec3b>(Point(x, y))[1] = image4.at<Vec3b>(Point(x, y))[1];
				image3.at<Vec3b>(Point(x, y))[2] = image4.at<Vec3b>(Point(x, y))[2];
			}

		}

	imshow("���त�����ꪺ��", image3);

}

int main()
{

	while (true)
	{
		string path = "";
		cout << "\n�п�J�Ϥ����|(�Y�n�h�X,�h��J0): ";

		getline(cin, path);
		if (path == "0")
			break;

		image = imread(path, -1);  // -1 �@�w�n��

		if (image.empty())
		{
			cout << "\n�Ϥ������|���~\n";
			continue;
		}

		image2 = image.clone(); // �s�u���Χ��Ϥ���A�ѤU����v
		image3 = image.clone();// �s �u���Χ��Ϥ���A�ѤU���I���v

		cout << "\n�п�J���ਤ��:";
		angle = 0;

		while (cin >> angle)
		{
			angle2 = angle;

			height = image.rows;  
			width = image.cols;	
			radius = min(height, width) / 2;  

			center = Point(width / 2, height / 2);

			for (int x = 0; x < width; x++)
				for (int y = 0; y < height; y++)
				{
					int temp = (x - center.x) * (x - center.x) + (y - center.y) * (y - center.y);  // �C�Ӯy�лP��ߪ��Z��

					if (temp < (radius * radius))  // ���ΥX�ꪺ����
					{
						image2.at<Vec3b>(Point(x, y))[0] = image.at<Vec3b>(Point(x, y))[0];
						image2.at<Vec3b>(Point(x, y))[1] = image.at<Vec3b>(Point(x, y))[1];
						image2.at<Vec3b>(Point(x, y))[2] = image.at<Vec3b>(Point(x, y))[2];

					}
					else  // ���ΥX�I��������(���]�A��)
					{
						image3.at<Vec3b>(Point(x, y))[0] = image.at<Vec3b>(Point(x, y))[0];
						image3.at<Vec3b>(Point(x, y))[1] = image.at<Vec3b>(Point(x, y))[1];
						image3.at<Vec3b>(Point(x, y))[2] = image.at<Vec3b>(Point(x, y))[2];

					}

				}

			namedWindow("���", WINDOW_AUTOSIZE);
			namedWindow("�����i�Ϥ�����", WINDOW_AUTOSIZE);
			namedWindow("���त�����ꪺ��", WINDOW_AUTOSIZE);

			imshow("���", image);
			
			//�b�������إߤ@�ӷưʱ�
			char TranckbarName[50] = "���ਤ��";
			createTrackbar(TranckbarName, "�����i�Ϥ�����", &angle, MaxAngle, on_trackbar1);
			createTrackbar(TranckbarName, "���त�����ꪺ��", &angle2, MaxAngle, on_trackbar2);

			on_trackbar1(angle, 0);
			on_trackbar2(angle2, 0);

			waitKey(0);

			destroyWindow("���");
			destroyWindow("�����i�Ϥ�����");
			destroyWindow("���त�����ꪺ��");

			cout << "\n�п�J���ਤ��:";
		}
		cin.clear(); // ���F�N ^Z ��J�y,�M��

	}

}
