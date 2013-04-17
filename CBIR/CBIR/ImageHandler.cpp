#include"ImageHandler.h"
#include<iostream>
#include<fstream>


void ImageHandler::loadImage(char* imagePath)
{
	/*
	if(imagePath != NULL)
	{
		cvReleaseImage(&m_Image); 
		m_Image = cvLoadImage(imagePath,CV_LOAD_IMAGE_COLOR);
	}
	else
		m_Image = NULL;*/
}
/**
dimension:ָ����RGBÿ��ά���ϵķ���
*/
 ColorHistogram ImageHandler::extractColorHostogram(char* imagePath, int dim)
{
	ColorHistogram colorHis;
	/*
	int dimension = dim * dim * dim;  //����ά���Ͼ���
	colorHis.dimNo = dimension;
	int w, h, index;
	CvScalar s;
	for(w = 0; w < dimension; w++)
		colorHis.his[w] = 0.0;

	if(dimension == 9)
	{
		loadImage(imagePath);
		if(imagePath != NULL)
		{
			int width = m_Image->width;
			int height = m_Image->height;
			
			for(h = 0; h < height; h++)
			{
				for(w = 0; w <width; w++)
				{
					s = cvGet2D(m_Image,h, w);
					index = ((int)s.val[0] / dim) *((int)s.val[1]/dim) * ((int)s.val[2]/dim); 
					if(index == dimension)
						index --;
					colorHis.his[index]++;
				}
			}
		}
	}*/
	return colorHis;
}


 //�����ļ�������ʽ���һ���ļ�����ǩ
 ImageTag ImageHandler::parseImageName(string imageName)
 {
	 ImageTag imageTag;
	 int index1 = imageName.find('_');  
	 int index2 = imageName.find('.');
	 string catagory = imageName.substr(1, index1 - 1);
	 string index = imageName.substr(index1 + 1, index2 -index1);
	 imageTag.catagory = atoi(catagory.c_str());
	 imageTag.index = atoi(index.c_str());
	 //cout << catagory  << "," << index << endl;
	 return imageTag;
 }

 //�Զ��ؽ���ͼ����Ϣͳ�ƣ��ļ�����ͳ��/�ļ����б���ص��ڴ�
 void ImageHandler::inputImageInformation()
 {

	 ifstream fileIn(imageListFilePath, ios::in);
     ImageTag imageTag;
	 
	 string fileName;
	 string imagePath;
	 hash_map<int, int>::iterator it;
	 while(!fileIn.eof())
	 {
		 char buffer[30];
		 fileIn.getline(buffer, 30);   //��ȡ�ļ������ƣ��������buffer��
		 fileName = buffer;              
		 imageList[imageNumber] = fileName;  //���ļ�������ӵ�vector����
		 imageTag = parseImageName(fileName);
		 imageInfo.find(imageTag.catagory);
		 it = imageInfo.find(imageTag.catagory);
		 if(it == imageInfo.end())
		 {
			 imageInfo[imageTag.catagory] = 1;
		 }
		 else
		 {
			 imageInfo[imageTag.catagory] += 1;
		 }
		 imageNumber++;

		 /*
		 imagePath = fileDepositoryPath + '/' + fileName; 
		 //���濪ʼ��ȡͼ���ļ�
		 //���ļ��������д���
		 //���ļ�����д��ָ���ļ���*/
	 }

	 fileIn.close();
 }

 //���������ļ���Ϣ������ָ�����͵������ļ������ҷ���һ�������ṹ
void ImageHandler::constructImageIndexFromFeatureFile(RTree<int,double,9,double> &rtree,char* inFeatureFilePath)
 {
	 ifstream fileIn(inFeatureFilePath, ios::in);
	 //ofstream fileOut("G:\/ѧҵ��H\/�����¿γ�\/�߼����ݽṹ\/�γ���ҵ\/ADS-Project1-Release\/ADS-Project1-Release\/data\/color_feature_double.txt", ios::app);
	 int i = 0;
	 char buffer[60];
	 string feature;
	 ColorComment colorComment;
	
	 while(!fileIn.eof())
	 {
		 fileIn.getline(buffer,60);
		 feature = buffer;

		 if(feature[0] == 'r')
		 {
			 colorComment = parserImageCommentFeature(feature);
			 /*
			 fileOut << "rect ";
			 for(int k = 0; k <9; k++)
			 {
				 fileOut << colorComment.data[k]/100.0 << " ";
			 }
			 fileOut << endl;*/
			 rtree.Insert(colorComment.data, colorComment.data,i);  //��������ӵ�RTree��
			 i++;
		 }
		 
	 }
	 fileIn.close();
	 //fileOut.close();
}
ColorComment ImageHandler::parserImageCommentFeature(string feature)
{
	ColorComment colorComment;
	int index, i;
	feature = feature.substr(5);
	for(i = 0; i < 8; i++)
	{
		index = feature.find(' ');
		colorComment.data[i] = atof(feature.substr(0, index).c_str());
		feature = feature.substr(index + 1);
	}
	colorComment.data[8] = atoi(feature.c_str());// / 10000.0;
	return colorComment;
}


