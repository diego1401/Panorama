# Panorama
![This is an image](/Panorama_Initial/ex_tmp.png)

## To run

- Install Imagine++ (http://imagine.enpc.fr/~monasse/Imagine++/)
- Follow the tutorial to see how to run the test files of this library.
- With the same procedure you can now run the above folder.

## Instructions

Add the 2 photos from which you want to create your panorama to the folder. In the file `Panorama.cpp`, in the function `main` replace with the name of your jpg file in these 2 lines:
```
const char* s1 = argc>1? argv[1]: srcPath(IMAGE_NAME1);
const char* s2 = argc>2? argv[2]: srcPath(IMAGE_NAME2);
```

Now, run the program. Your 2 images will pop up, you will then have to **right** click **at least 4 matching points**. Once you have chosen your desired points do a **left click** in the first image. See the example of selection below.

![This is an image](/Panorama_Initial/figures/image1_selection.png)
