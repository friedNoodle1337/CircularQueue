#ifndef QUEUE_HPP
#define QUEUE_HPP

template < class T >
class Queue
{
public:
	virtual ~Queue() {}

	virtual void enqueue(const T& e) = 0;
	virtual T dequeue() = 0;
	virtual bool isEmpty() const = 0;
};

#endif
