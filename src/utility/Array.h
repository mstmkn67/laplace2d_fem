#ifndef _ARRAY_H_
#define _ARRAY_H_

////////////////////Array1d////////////////////////
template<class T>
class Array1d{
public:
	Array1d<T>():array(0){}
	//Array1d<T>(int x):array(0){setSize(x);}
	Array1d<T>(int x):array(0){resize(x);}
	virtual ~Array1d<T>(){freeArray();}
	//set size of array
	virtual void resize(int x){
		if(array!=0)freeArray();
		n[0]=x;array=new T[n[0]];
	}
	//acceptable read and write
	virtual T& operator[](int i){return array[i];}
	//read only
	virtual T operator()(int i)const{return array[i];}
	//return size of array
	virtual int* size(){return n;}
	//return starting address of array
	virtual T* add(){return (T*)array;}
private:
	virtual void freeArray(){delete[] array;}
	T* array;
	int n[1];
};
////////////////////Array2d////////////////////////
template<class T>
class Array2d{
public:
	Array2d<T>():array(0){}
	Array2d<T>(int x,int y):array(0){resize(x,y);}
	virtual ~Array2d<T>(){freeArray();}
	//set size of array
	virtual void resize(int x,int y){
		if(array!=0)freeArray();
		n[0]=x;n[1]=y;
		array=new T*[n[0]];
		array[0]=new T[n[0]*n[1]];
		for(int i=1;i<n[0];i++)array[i]=array[0]+i*n[1];
	}
	//acceptable read and write
	virtual T* operator[](int i){return array[i];}
	//read only
	virtual T operator()(int i,int j)const{return array[i][j];}
	//return size of array
	virtual int* size(){return n;}
	//return starting address of array
	virtual T* add(){return array[0];}
private:
	virtual void freeArray(){
		delete[] array[0];
		delete[] array;
	}
	T** array;
	int n[2];
};
////////////////////Array3d////////////////////////
template<class T>
class Array3d{
public:
	Array3d<T>():array(0){}
	Array3d<T>(int x,int y,int z):array(0){resize(x,y,z);}
	virtual ~Array3d<T>(){freeArray();}
	//set size of array
	virtual void resize(int x,int y,int z){
		if(array!=0)freeArray();
		n[0]=x;n[1]=y;n[2]=z;
		array=new T**[n[0]];
		array[0]=new T*[n[0]*n[1]];
		for(int i=1;i<n[0];i++)array[i]=array[0]+i*n[1];
		array[0][0]=new T[n[0]*n[1]*n[2]];
		{for(int i=1;i<n[0]*n[1];i++){
			int x=i%n[0],y=i/n[0];
			array[x][y]=array[0][0]+i*n[2];
		}}
	}
	//acceptable read and write
	virtual T** operator[](int i){return array[i];}
	//read only
	virtual T operator()(int i,int j,int k)const{return array[i][j][k];}
	//return size of array
	virtual int* size(){return n;}
	//return starting address of array
	virtual T* add(){return array[0][0];}
private:
	virtual void freeArray(){
		delete[] array[0][0];
		delete[] array[0];
		delete[] array;
	}
	T*** array;
	int n[3];
};
#endif // _ARRAY_H_
