#include <exception>

#include "CircularQueue.hpp"

int main()
{
  try
  {
    CircularQueue< char > queue(5);

    std::cout << "Inserting... ";
    queue.enqueue('a');
    queue.enqueue('b');
    queue.enqueue('c');
    queue.enqueue('d');
    queue.enqueue('e');
    std::cout << "Complete!\n";

    std::cout << "\nDequeueing... (and inserting at the same time)\n";
    std::cout << queue.dequeue() << " ";
    std::cout << queue.dequeue() << " ";
    queue.enqueue('f');
    std::cout << queue.dequeue() << " ";
    queue.enqueue('a');
    queue.print(4);
    queue.dequeue();
    queue.dequeue();
    queue.dequeue();
    queue.dequeue();

    std::cout << "\nTesting of constructors and operator=: \n";
    queue.enqueue('a');
    queue.enqueue('b');
    queue.enqueue('c');
    queue.enqueue('d');
    queue.enqueue('e');
    std::cout << "\nQueue1: \n";
    queue.print(5);

    if (true)
    {
      CircularQueue< char > queue2(queue);

      std::cout << "\nQueue2 (copy constructor): \n";
      queue2.print(5);
      queue2.dequeue();
      queue2.dequeue();
      queue2.dequeue();
      queue2.dequeue();
      queue2.dequeue();
      std::cout << "Queue1: \n";
      queue.print(5);

      std::cout << "\nQueue2 (copy operator=): \n";
      queue2 = queue;
      queue2.print(5);
      std::cout << "Queue1: \n";
      queue.print(5);
    }

    if (true)
    {
      CircularQueue< char > queue2(std::move(queue));
      CircularQueue< char > temp(5);

      std::cout << "\nQueue2 (move constructor): \n";
      queue2.print(5);
      std::cout << "Queue1: \n";
      queue.print(5);

      temp.enqueue('f');
      temp.enqueue('g');
      temp.enqueue('h');
      temp.enqueue('j');
      temp.enqueue('k');
      std::cout << "\nTemp queue: \n";
      temp.print(5);

      std::cout << "Queue2 (move operator=): \n";
      queue2 = std::move(temp);
      queue2.print(5);
      std::cout << "Temp queue: \n";
      temp.print(5);
    }

    std::cout << "\nTesting of constructors and operator= is successfully completed!\n";
  }
  catch (const CircularQueue< char >::CircularQueueException& exc)
  {
    std::cerr << exc.getMessage() << "\n";
  }
  catch (const std::exception& exc)
  {
    std::cerr << exc.what() << "\n";
  }

  return 0;
}
