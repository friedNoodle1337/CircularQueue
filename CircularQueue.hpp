#ifndef CIRCULARQUEUE_HPP
#define CIRCULARQUEUE_HPP

#include <iostream>
#include <limits>
#include <string>

#include "Queue.hpp"

template < class T >
class CircularQueue: public Queue< T >
{
public:
	CircularQueue(size_t capacity = 100);
	CircularQueue(const CircularQueue< T >& other);
	CircularQueue(CircularQueue< T >&& other) noexcept;
	virtual ~CircularQueue() noexcept;

	CircularQueue< T >& operator=(const CircularQueue< T >& other);
	CircularQueue< T >& operator=(CircularQueue< T >&& other) noexcept;

	void enqueue(const T& e) override;
	T dequeue() override;
	bool isEmpty() const override;
	bool isFull() const;
	void print(size_t n, std::ostream& out = std::cout);

	class CircularQueueException
	{
	public:
		CircularQueueException(const std::string message): message_(message) {}
		virtual const std::string getMessage() const { return message_; }

	private:
		std::string message_;
	};

private:
	T* array_;
	size_t capacity_;
	int front_;
	int rear_;

	void swap(CircularQueue< T >& other)
	{
		std::swap(array_, other.array_);
		std::swap(front_, other.front_);
		std::swap(rear_, other.rear_);
		std::swap(capacity_, other.capacity_);
	}
};

template < class T >
class CircularQueueOverflow: public CircularQueue< T >::CircularQueueException
{
public:
	CircularQueueOverflow(const std::string message = "Circular Queue Overflow"): CircularQueueException(message) {}
};

template < class T >
class CircularQueueUnderflow: public CircularQueue< T >::CircularQueueException
{
public:
	CircularQueueUnderflow(const std::string message = "Circular Queue Underflow"): CircularQueueException(message) {}
};

template < class T >
class WrongCircularQueueSize: public CircularQueue< T >::CircularQueueException
{
public:
	WrongCircularQueueSize(const std::string message = "Wrong Circular Queue Size"): CircularQueueException(message) {}
};

template < class T >
CircularQueue< T >::CircularQueue(size_t capacity):
	array_(nullptr),
	front_(-1),
	rear_(-1)
{
	if (capacity >= std::numeric_limits< size_t >::min() && capacity < std::numeric_limits< size_t >::max())
	{
		capacity_ = capacity;
		array_ = new T[capacity];
	}
	else
	{
		throw WrongCircularQueueSize< T >();
	}
}

template < class T >
CircularQueue< T >::CircularQueue(const CircularQueue< T >& other):
	array_(nullptr),
	front_(other.front_),
	rear_(other.rear_)
{
	if (other.capacity_ >= std::numeric_limits< size_t >::min() && other.capacity_ < std::numeric_limits< size_t >::max())
	{
		capacity_ = other.capacity_;
		array_ = new T[other.capacity_];
	}
	else
	{
		throw WrongCircularQueueSize< T >();
	}
	for (size_t i = 0; i < capacity_; ++i)
	{
		array_[i] = other.array_[i];
	}
}

template < class T >
CircularQueue< T >::CircularQueue(CircularQueue< T >&& other) noexcept:
	array_(other.array_),
	capacity_(other.capacity_),
	front_(other.front_),
	rear_(other.rear_)
{
	other.array_ = nullptr;
	other.capacity_ = 0;
	other.front_ = -1;
	other.rear_ = -1;
}

template < class T >
CircularQueue< T >::~CircularQueue() noexcept
{
	delete[] array_;
	array_ = nullptr;
	capacity_ = 0;
	front_ = -1;
	rear_ = -1;
}


template < class T >
CircularQueue< T >& CircularQueue< T >::operator=(const CircularQueue< T >& other)
{
	if (this != &other)
	{
		delete[] array_;
		capacity_ = other.capacity_;
		front_ = other.front_;
		rear_ = other.rear_;
		array_ = new T[capacity_];
		for (size_t i = 0; i < capacity_; ++i)
		{
			array_[i] = other.array_[i];
		}
	}

	return *this;
}

template < class T >
CircularQueue< T >& CircularQueue< T >::operator=(CircularQueue< T >&& other) noexcept
{
	if (this != &other)
	{
		swap(other);
	}

	return *this;
}

template < class T >
void CircularQueue< T >::enqueue(const T& e)
{
	if (isFull() == true)
	{
		throw CircularQueueOverflow< T >();
	}

	if (isEmpty() == true)
	{
		++front_;
	}

	++rear_ %= capacity_;
	array_[rear_] = e;
}

template < class T >
T CircularQueue< T >::dequeue()
{
	if (isEmpty() == true)
	{
		throw CircularQueueUnderflow< T >();
	}

	T temp = array_[front_];
	if (front_ == rear_)
	{
		front_ = -1;
		rear_ = -1;
	}
	else
	{
		++front_ %= capacity_;
	}

	return temp;
}

template < class T >
bool CircularQueue< T >::isEmpty() const
{
	return front_ == -1 && rear_ == -1;
}

template < class T >
bool CircularQueue< T >::isFull() const
{
	return (rear_ + 1) % capacity_ == front_;
}

template < class T >
void CircularQueue< T >::print(size_t n, std::ostream& out)
{
	if (array_ != nullptr)
	{
		T buff = dequeue();
		out << buff;
		enqueue(buff);
		for (size_t i = 0; i < n - 1; i++)
		{
			buff = dequeue();
			out << " " << buff;
			enqueue(buff);
		}
		out << "\n";
	}
	else
	{
		out << "Empty\n";
	}
}

#endif
