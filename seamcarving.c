#include "seamcarving.h"
#include <stdio.h>
#include <math.h>

void calc_energy(struct rgb_img *im, struct rgb_img **grad){
    create_img(grad, im->height,im->width);
    int e_x;
    int e_y;
    for(int i = 0; i < im->height; i++){
        for(int j = 0; j < im->width; j++){
                if (j!=0 && j!=(im->width)-1){
                   int r_front = get_pixel(im,i,j+1,0);
                   int r_back = get_pixel(im,i,j-1,0);
                   int g_front = get_pixel(im,i,j+1,1);
                   int g_back = get_pixel(im,i,j-1,1);
                   int b_front = get_pixel(im,i,j+1,2);
                   int b_back = get_pixel(im,i,j-1,2);
                   int R_x = r_front - r_back;
                   int G_x= g_front - g_back;
                   int B_x = b_front - b_back;
                   e_x = pow(R_x,2)+pow(G_x,2)+pow(B_x,2);
                }
                else if (j==(im->width)-1){
                   int r_front = get_pixel(im,i,0,0);
                   int r_back = get_pixel(im,i,j-1,0);
                   int g_front = get_pixel(im,i,0,1);
                   int g_back = get_pixel(im,i,j-1,1);
                   int b_front = get_pixel(im,i,0,2);
                   int b_back = get_pixel(im,i,j-1,2);
                   int R_x = r_front - r_back;
                   int G_x= g_front - g_back;
                   int B_x = b_front - b_back;
                   e_x = pow(R_x,2)+pow(G_x,2)+pow(B_x,2);

                }
                else if(j==0){
                   int end = im-> width-1;
                   int r_front = get_pixel(im,i,j+1,0);
                   int r_back = get_pixel(im,i,end,0);
                   int g_front = get_pixel(im,i,j+1,1);
                   int g_back = get_pixel(im,i,end,1);
                   int b_front = get_pixel(im,i,j+1,2);
                   int b_back = get_pixel(im,i,end,2);
                   int R_x = r_front - r_back;
                   int G_x= g_front - g_back;
                   int B_x = b_front - b_back;
                   e_x = pow(R_x,2)+pow(G_x,2)+pow(B_x,2);
                }
                if(i!=0 && i!=(im->height)-1){
                   int r_up = get_pixel(im,i-1,j,0);
                   int r_down = get_pixel(im,i+1,j,0);
                   int g_up = get_pixel(im,i-1,j,1);
                   int g_down = get_pixel(im,i+1,j,1);
                   int b_up = get_pixel(im,i-1,j,2);
                   int b_down = get_pixel(im,i+1,j,2);
                   int R_y = r_up - r_down;
                   int G_y= g_up - g_down;
                   int B_y = b_up - b_down;
                   e_y = pow(R_y,2)+pow(G_y,2)+pow(B_y,2);
                }
                else if(i==(im->height)-1){
                   int r_up = get_pixel(im,i-1,j,0);
                   int r_down = get_pixel(im,0,j,0);
                   int g_up = get_pixel(im,i-1,j,1);
                   int g_down = get_pixel(im,0,j,1);
                   int b_up = get_pixel(im,i-1,j,2);
                   int b_down = get_pixel(im,0,j,2);
                   int R_y = r_up - r_down;
                   int G_y= g_up - g_down;
                   int B_y = b_up - b_down;
                   e_y = pow(R_y,2)+pow(G_y,2)+pow(B_y,2);

                }
                else if(i==0){
                   int end = (im->height)-1;
                   int r_up = get_pixel(im,end,j,0);
                   int r_down = get_pixel(im,i+1,j,0);
                   int g_up = get_pixel(im,end,j,1);
                   int g_down = get_pixel(im,i+1,j,1);
                   int b_up = get_pixel(im,end,j,2);
                   int b_down = get_pixel(im,i+1,j,2);
                   int R_y = r_up - r_down;
                   int G_y= g_up - g_down;
                   int B_y = b_up - b_down;
                   e_y = pow(R_y,2)+pow(G_y,2)+pow(B_y,2);
                }
                 int e_tot =  sqrt(e_x + e_y);
                 uint8_t energy = e_tot/10;

                 set_pixel(*grad,i,j,energy,energy,energy);



                }


                }
               // write_img(*grad,"grad.bin");



}

int min(int *a, int *b){
        if (a>=b){
            return b;
        }else{
            return a;
        }


}
void dynamic_seam(struct rgb_img *grad, double **best_arr){

    int w = grad->width;
    int i=1;
    *best_arr = (double *)malloc(sizeof(double)*(grad->width)*(grad->height));
    int a;
    int k =0;

    int value;
    for (int r=0; r< (grad->width);r++){

        value = get_pixel(grad,0,r,0);
        (*best_arr)[k*w + r]= (double) value;
        //printf("%f\n",(*best_arr)[k*w+r]);
    }



    while (i<grad->height){
        int j =0;
        while(j<grad ->width){

            if(j==0){
                    int first =(*best_arr)[(i-1)*w + j];
                    int second = (*best_arr)[(i-1)*w + j+1];
                    (*best_arr)[i*w + j] = get_pixel(grad,i,j,0) +min(first,second);
            }
            else if(j==grad->width - 1){
                    int first =(*best_arr)[(i-1)*w + j-1];
                    int second = (*best_arr)[(i-1)*w + j];
                (*best_arr)[i*w + j]=get_pixel(grad,i,j,0)+min(first,second);
            }
            else{
                int first = (*best_arr)[(i-1)*w + j-1];
                int mid = (*best_arr)[(i-1)*w + j];
                int last =(*best_arr)[(i-1)*w + j+1];
                if(mid<=min(last,first)){
                    (*best_arr)[i*w + j]=get_pixel(grad,i,j,0)+mid;
                }
                else{
                    (*best_arr)[i*w + j]=get_pixel(grad,i,j,0)+min(first, last);
                }
            }
           // printf("%f\n",(*best_arr)[i*w+j]);
            j++;

        }
        i++;
    }







}
void recover_path(double *best, int height, int width, int **path){

    *path = (int *)malloc(sizeof(int)*height);
     //best= (double *)malloc(sizeof(double)*width*height);
     int j;
     int cur_min;
     int cur_ind;
    int i = height-1;
    while (i>=0){
                if (i==height-1){
                    cur_min = 1000;
                    cur_ind = -1;
                    for(j=0;j<width;j++){
                        if((best)[i*width+j]<= cur_min){
                            cur_min = (best)[i*width +j];
                            cur_ind= j;
                            (*path)[i]=cur_ind;

                        }
                }
                }
                else{
                    j=cur_ind;
                    if(j==0){
                        if ((best)[i*width+j]<=(best)[i*width+j+1]){
                            (*path)[i]=j;
                            cur_ind=j;
                            }
                        else{
                            (*path)[i]=j+1;
                            cur_ind=j+1;
                        }
                    }
                    else if(j==width-1){
                        if((best)[i*width+j]<=(best)[i*width+j-1]){
                            (*path)[i]=j;
                            cur_ind=j;
                        }
                        else{
                            (*path)[i]=j-1;
                            cur_ind=j-1;
                        }

                    }
                    else{
                        int right = (best)[i*width+j+1];
                        int left = (best)[i*width+j-1];
                        if((best)[i*width+j]<=min(right,left)){
                            (*path)[i]=j;
                            cur_ind = j;
                        }
                        else{
                            if((best)[i*width+j+1]<=(best)[i*width+j-1]){
                                (*path)[i]=j+1;
                                cur_ind = j+1;
                            }
                            else{
                                (*path)[i]=j-1;
                                cur_ind= j-1;
                            }
                        }
                    }
                }

            //printf("%d",(*path)[i]);
            i--;


    }
//    for(int r=0;r<height;r++ ){
//       // printf("%d",(*path)[r]);
//    }



}
void remove_seam(struct rgb_img *src, struct rgb_img **dest, int *path){

     create_img(dest, (src->height),(src->width)-1);
     for (int i=0;i<src->height;i++){
        int k = 0;
        for(int j =0;j<src->width;j++){

            if(j!=path[i]){
                uint8_t r = get_pixel(src,i,j,0);
                uint8_t g = get_pixel(src,i,j,1);
                uint8_t b = get_pixel(src,i,j,2);
                set_pixel(*dest,i,k,r,g,b);
                k++;
            }
            else{
                continue;
            }
        }



     }



}

