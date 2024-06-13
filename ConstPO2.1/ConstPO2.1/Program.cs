using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConstPO2._1
{
    class Stack
    {
        static int MaxId = 1;

        string StackId;
        int MaxSize;
        string[] st;
        int top;

        public Stack(int maxSize = 100)
        {
            MaxSize = maxSize;
            top = 0;
            st = new string[MaxSize];
            StackId = MaxId.ToString();
            MaxId++;
            Console.WriteLine($"Создан стек {StackId}!");
        }

        public void Push(string c)
        {
            if (top < MaxSize)
            {
                st[top++] = c;
            }
            else
            {
                Console.WriteLine("Стек переполнен!");
            }
        }

        public string? Pop()
        {
            if (top > 0)
            {
                top--;
                return st[top];
            }
            else
            {
                Console.WriteLine("Стек пуст!");
                return null;
            }
        }
    }

    class Programm
    {

        static void Main()
        {
            string? s;
            string r;
            Stack stack = new Stack();
            do
            {
                Console.WriteLine("Что сдлеать?");
                s = Console.ReadLine();
                if (s == "заложить")
                {
                    Console.WriteLine("Что?");
                    r = Console.ReadLine() ?? "";
                    stack.Push(r);
                }
                if (s == "достать")
                {
                    Console.WriteLine(stack.Pop());
                }
            } while (s != "выйти");
        }
    }
}
