#pragma once
#include<iostream>
#include<exception>
template<typename H, typename T>
struct typelist
{
	typedef H head;
	typedef T tail;
};
struct null_typelist
{
};
template<typename tylist> class visitor;

class DocumentElement;
template<typename H, typename T>
class visitor<typelist<H, T>> : visitor<T> {
public:
	using visitor<T>::visit;
	virtual void visit(H*) = 0;

	template<typename _Ele>
	void DoVisit(_Ele* ele) {
		if (H* type=dynamic_cast<H*>(ele)) {
			visit(type);
		}
		else {
			visitor<T>::DoVisit(ele);
		}
	}
};
template<typename H>
class visitor < typelist<H, null_typelist> > {
public:
	virtual void visit(H*) = 0;
	template<typename _Ele>
	void DoVisit(_Ele* ele) {
		if (H* type=dynamic_cast<H*>(ele)) {
			visit(type);
		}
		else throw std::exception("Wrong class");
	}
};

class ConcreteVisitor;

class DocumentElement {
public:
	virtual void draw() = 0;
};
class text : public DocumentElement {
public:
	virtual void draw() {
		std::cout << "text\n";
	}
};
class image : public DocumentElement {
public:
	virtual void draw() {
		std::cout << "image\n";
	}
};
class video : public DocumentElement {
public:
	virtual void draw() {
		std::cout << "video\n";
	}
};

typedef typelist<text, typelist<image, typelist < video, null_typelist> >> DocumentElementList;

class ConcreteVisitor : public visitor<DocumentElementList>
{
public:
	ConcreteVisitor(){}
	~ConcreteVisitor(){}
	void visit(text* ele) {
		std::cout << "Text is here\n";
	}
	void visit(image* img) {
		std::cout << "Image is here\n";
	}
	void visit(video* vd) {
		std::cout << "Video is here\n";
	}
};

int main() {
	ConcreteVisitor cv;
	DocumentElement* vd= new video;
	cv.DoVisit(vd);
}





