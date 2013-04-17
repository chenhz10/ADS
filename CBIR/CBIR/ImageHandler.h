#include"ImageFeature.h"
#include"RTree.h"
#include<highgui.h>
#include<string>
#include<hash_map>
#include<vector>

using namespace std;


//ͼ�����Ʒ����� ncatagory_index.JPG
struct ImageTag
{
	int catagory;           //��ʾͼ�������
	int index;              //ͼ�������µ��±�
};

struct  ColorHistogram
{
	int dimNo;   //��״ֱ��ͼ��ά��
	float* his;  //��ʾ��ά������
};


struct ColorComment
{
	double data[9];
};




class ImageHandler{
	
public:
	string imageList[5613];

private:
	/*IplImage* m_Image;*/
	
	hash_map<int, int> imageInfo;   //ͳ��ͼ�����ͼ���Ϣ
	int imageNumber;                //��¼ͼ�������Ŀ
	char *fileDepositoryPath;       //ͼ��Ĵ���·��
	char* imageListFilePath;        //�ļ����б��ļ�·��
	
	
	void loadImage(char* imagePath); //

public: 
	
	ImageHandler(){ /*m_Image = NULL;*/imageNumber = 0; imageInfo = hash_map<int,int>();}
	void setFileDepositoryPath(char* fileDepositoryPath ){this->fileDepositoryPath = fileDepositoryPath;}
	void setImageListFilePath(char* imageListFilePath){this->imageListFilePath  = imageListFilePath;}

	ColorHistogram extractColorHostogram(char* imagePath, int dimension); //��ȡ��ɫֱ��ͼ
	ImageTag parseImageName(string imageName);//�ļ�·����ȡͼƬ���������Ҹ���Ŀ¼�����ƽ��з���
	ColorComment parserImageCommentFeature(string feature);
	void inputImageInformation(); 
	void constructImageIndexFromFeatureFile(RTree<int,double,9,double> &rtree,char* inFeatureFilePath);
};