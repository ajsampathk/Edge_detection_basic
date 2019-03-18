#include<CImg.h>
#include<stdio.h>
#include<cmath>
using namespace cimg_library;

CImg<double> greyscale(CImg<double> image)
{
  CImg<double> comp(image.width(),image.height(),1,1,0);
  for(int i=0; i<image.width(); i++)
  {
    for(int y=0; y<image.height(); y++)
    {
       comp(i,y,0,0)= ((image(i,y,0,0)+image(i,y,0,1)+image(i,y,0,2))/3);
    }
  }
  return comp;
}

CImg<double> binary(CImg<double> comp,float low=30)
{
  for(int i=0; i<comp.width(); i++)
    for(int y=0; y<comp.height(); y++)
       comp(i,y,0,0)= comp(i,y,0,0)>low?255:0;
  return comp;
}

CImg<double> filter(CImg<double> comp)
{
   double str=0;
   CImg<double> blur(comp.width(),comp.height(),1,1,0);
   for (int i = 1; i<(comp.width()-1); i++)
   {
    for (int j = 1; j<(comp.height()-1);j++)
    {
      str = (comp(i-1,j-1,0,0)+comp(i,j-1,0,0)+comp(i+1,j-1,0,0)+comp(i-1,j,0,0)+comp(i,j,0,0)+comp(i+1,j,0,0)+comp(i-1,j+1,0,0)+comp(i,j+1,0,0)+comp(i+1,j+1,0,0))/9;
      for(int x=i-1; x<=i+1; x++)
      {
        for(int y = j-1; y<=j+1; y++)
        {
          blur(x,y,0,0)=str;
        }
      }
    }
  }
  return blur;
}

CImg<double> mask(CImg<double> comp,float val[3][3])
{
  double str=0;
  CImg<double> blur(comp.width(),comp.height(),1,1,0);

  for (int i = 1; i<(comp.width()-1); i++)
  {
   for (int j = 1; j<(comp.height()-1);j++)
   {
     str = ((comp(i-1,j-1,0,0)*val[0][0])+(comp(i,j-1,0,0)*val[0][1])+(comp(i+1,j-1,0,0)*val[0][2])+(comp(i-1,j,0,0)*val[1][0])+(comp(i,j,0,0)*val[1][1])+(comp(i+1,j,0,0)*val[1][2])+(comp(i-1,j+1,0,0)*val[2][0])+(comp(i,j+1,0,0)*val[2][1])+(comp(i+1,j+1,0,0)*val[2][2]))/9;
         blur(i,j,0,0)=str;
   }
 }
 return blur;
}

CImg<double> sobel(CImg<double> blur)
{
  CImg<double> x_k(blur.width(),blur.height(),1,1,0);
  CImg<double> y_k(blur.width(),blur.height(),1,1,0);
  CImg<double> gradient(blur.width(),blur.height(),1,1,0);
  // CImg<double> theta(blur.width(),blur.height(),1,1,0);

  float x[3][3]={{-1,-1.414,-1},{0,0,0},{1,1.414,1}},y[3][3]={{-1,0,1},{-1.414,0,1.414},{-1,0,1}};
  // float angle;
  y_k = mask(blur,x);
  x_k = mask(blur,y);
  // CImgDisplay xgrad(x_k,"X-Grad",0);
  // CImgDisplay ygrad(y_k,"Y-Grad",0);
  // while(1);
  for (int i = 1; i<(blur.width()-1); i++)
  {
   for (int j = 1; j<(blur.height()-1);j++)
   {
     gradient(i,j,0,0) = sqrt((x_k(i,j,0,0)*x_k(i,j,0,0)) + (y_k(i,j,0,0)*y_k(i,j,0,0)));
     // angle = ((atan(y_k(i,j,0,0)/x_k(i,j,0,0))));

   }
 }
 return gradient;
}

CImg<double> enhance(CImg<double> image,float u=2){

  CImg<double> enhanced(image.width(),image.height(),1,1,0);
  float pixel;
  for (int i = 0; i<(image.width()); i++)
  {
   for (int j = 0; j<(image.height());j++)
   {
     pixel = u*image(i,j,0,0);
     enhanced(i,j,0,0) = pixel>255? 255:pixel;
     // angle = ((atan(y_k(i,j,0,0)/x_k(i,j,0,0))));

   }
}
return enhanced;
}


int main()
{
  float val[3][3]={{-1,1.414,1},{-1.414,3.1415,1.414},{-1,1.414,1}};

  CImg<double> image("./res/insta.png");
  CImgDisplay original(image,"Original",0);
  CImg<double> grey(image.width(),image.height(),1,1,0);
  CImg<double> bin(image.width(),image.height(),1,1,0);
  CImg<double> blur(grey.width(),grey.height(),1,1,0);
  CImg<double> new_k(blur.width(),blur.height(),1,1,0);



  grey = greyscale(image);
  CImgDisplay greyscale(grey,"grey",0);
  grey.save("./saved/grey_scale.png");


  blur = mask(grey,val);
  CImgDisplay blured(blur,"Blur",0);
  blur.save("./saved/blur.png");


  new_k = enhance(sobel(blur),1);
  CImgDisplay sobel_operator(new_k,"Edges",0);
  new_k.save("./saved/edges.png");


  bin = binary(new_k,5);
  CImgDisplay binary(bin,"Threshold-Edges",0);
  bin.save("saved/ThresholdEdges.png");


  while(1);
}
