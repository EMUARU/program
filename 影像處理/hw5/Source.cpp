#include<opencv2/opencv.hpp>
#include<iostream>
#define PI 3.1415926

using namespace cv;
using namespace std;

/*
	����:
	 C:\Users\User\Desktop\�v���B�z\hw5\Assignment5\flower.jpg
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

		Mat hsi(original.rows, original.cols, original.type());

		if (src.empty())
		{
			cout << "\n�Ϥ������|���~\n";
			continue;
		}

		float r, g, b, H, S, I, num, den, theta, sum, min_RGB;

		for (int i = 0; i < original.rows; i++)   // �N �ϱq "RGB color space" �ন "HSI color space" �C�p���ϧγB�z�ɡA�����|���Ӧh���T
		{
			for (int j = 0; j < original.cols; j++)
			{
				b = original.at<Vec3b>(i, j)[0];
				g = original.at<Vec3b>(i, j)[1];
				r = original.at<Vec3b>(i, j)[2];

				// �k�@��
				b = b / 255.0;
				g = g / 255.0;
				r = r / 255.0;



				num = 0.5 * ((r - g) + (r - b));
				den = sqrt((r - g) * (r - g) + (r - b) * (g - b));
				theta = acos(num / den);

				if (den == 0)
					H = 0; // �������ର0
				else
					if (b <= g)
						H = theta;
					else
						H = (2 * PI - theta);

				min_RGB = min(min(b, g), r);  // min(R,G,B)
				sum = b + g + r;

				if (sum == 0)
					S = 0;
				else
					S = 1 - 3 * min_RGB / sum;

				I = sum / 3.0;
				H = H / (2 * PI);

				//�NS���q�MH���q���X�R��[0,255]�϶��H�K�����;
				//�@��H���q�b[0,2pi]�����AS�b[0,1]����
				hsi.at<Vec3b>(i, j)[0] = H * 255;
				hsi.at<Vec3b>(i, j)[1] = S * 255;
				hsi.at<Vec3b>(i, j)[2] = I * 255;

			}

		}

		Mat binaryImage;

		// �]�w�n�������C�⪺�ƭȽd��(�������O�n�]�w����)�A�Ĥ@�ӰѼ�:�]�w�C��A�ĤG�ӰѼ�:�]�w���M�סA�ĤT�ӰѼ�:�]�w�j��
		Scalar scalarL = Scalar(22, 150, 0);  //�C��d�򪺤U��
		Scalar scalarH = Scalar(40, 255, 255); //�C��d�򪺤W��

		inRange(hsi, scalarL, scalarH, binaryImage);  //�ھڳ]�w���C��d��A�ͦ��@�i�G�Ȥƪ���(���Ϸ|�N�ؼ��C�⪺�ϰ�A�]���զ�)
		
		Mat result = original.clone();

		for (int i = 0; i < result.rows; i++)
			for (int j = 0; j < result.cols; j++)
			{
				int temp = binaryImage.at<uchar>(i, j);

				if (temp ==0)
				{
					result.at<Vec3b>(i, j)[0] = 0;
					result.at<Vec3b>(i, j)[1] = 0;
					result.at<Vec3b>(i, j)[2] = 0;
				}

			}



		namedWindow("���", WINDOW_AUTOSIZE);
		namedWindow("HSI��", WINDOW_AUTOSIZE);
		namedWindow("�G�Ȥƪ���", WINDOW_AUTOSIZE);
		namedWindow("���G", WINDOW_AUTOSIZE);

		resize(original, original, Size(), 0.5, 0.5);  //���ܹϤ����j�p�A0.5:��Ϫ�50%
		resize(hsi, hsi, Size(), 0.5, 0.5);
		resize(binaryImage, binaryImage, Size(), 0.5, 0.5);
		resize(result, result, Size(), 0.5, 0.5);

		imshow("���", original);
		imshow("HSI��", hsi);
		imshow("�G�Ȥƪ���", binaryImage);
		imshow("���G", result);


		waitKey(0);

		destroyWindow("���");
		destroyWindow("HSI��");
		destroyWindow("�G�Ȥƪ���");
		destroyWindow("���G");

		cin.clear();

	}

}