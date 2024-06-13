using System;
using System.Drawing;
using System.Linq;
using System.Reflection.Emit;
using System.Threading;
using System.Windows.Forms;
using static System.Net.Mime.MediaTypeNames;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;
using System.Collections.Generic;

namespace Course_paper
{
    public partial class Form1 : Form
    {
        public System.Drawing.Image image;  //класс изображения
        public Planet pl1, pl2;     //классы небесных тел
        public Asteroid ast;        //класс астероида
        public Zond zn;             //класс зонда
        Graphics g;                 //окно
        static public Color BackC = Color.FromArgb(0, 0, 0);  //цвет окна
        Random rnd = new Random(DateTime.Now.Millisecond);    //переменная для создания случайных чисел
        protected List<int> userParams = new List<int>(6);    //массив для хранения параметров, введенных пользователем

        public Form1()
        {
            InitializeComponent();
            this.BackColor = BackC; //установка цвета окна
            this.Width = 900;       //длина окна
            this.Height = 600;      //ширина окна
            this.DoubleBuffered = true; //форма сохраняет содержание
        }

        private void Form1_Load(object sender, EventArgs e)//загрузка
        {
            g = this.CreateGraphics();
            Choice(); //выбор модели
            this.KeyDown += new System.Windows.Forms.KeyEventHandler(Form1_KeyDown);
        }

        private void Timer1_Tick(object sender, EventArgs e) //Тела перемещаются после того, как время на таймере выйдет
        {
            pl1.Chase(pl2); //движение первого тела
            pl1.Moving(g);
            pl2.Chase(pl1); //движение второго тела
            pl2.Moving(g);  
            g.Clear(BackC); //очистка экрана

            pl1.Draw(g); //отрисовка первого тела
            pl2.Draw(g); //отрисовка второго тела

            //Проверка столкновения тел
            int distanceX = pl2.x + pl2.rad - pl1.x - pl1.rad;
            int distanceY = pl2.y + pl2.rad - pl1.y - pl2.rad;
            int distance = (int)Math.Sqrt(distanceX * distanceX + distanceY * distanceY); //высчитываем расстояние между телами
            if (distance <= pl1.rad + pl2.rad) //если расстояние меньше суммы двух радиусов
            {
                //Остановка таймера
                timer1.Enabled = false;
                Thread.Sleep(2000);
                g.Clear(BackC);
                Choice();
            }
        }//end Timer1_Tick

        private void Timer3_Tick(object sender, EventArgs e) //Тела перемещаются после того, как время на таймере выйдет
        {
            g.Clear(BackC); //очистка экрана

            ast.Moving(g);  //движение астероида
            zn.Moving(g);   //движение зонда

            ast.Draw(g); //отрисовка астероидa
            zn.Draw(g); //отрисовка зонда

            //Проверка приближения тел
            int distance = (int)Math.Sqrt((ast.x - zn.x) ^ 2 + (ast.y - zn.y) ^ 2); //высчитываем расстояние между телами
            if (distance <= 1)
            {
                zn.dx = 10;
            }
        }//end Timer1_Tick

        private void Form1_SizeChanged(object sender, EventArgs e) //если размер окна изменится
        {
            g = this.CreateGraphics();
        }

        private void Choice() //инициализация параметров небесных тел
        {
            //Отображаем сообщение с запросом выбора модели поведения небесных тел
            DialogResult dialogResult1 = MessageBox.Show("Выберите модель поведения небесных тел: " +
                                                        "нажмите 'Да' для Ньютоновского закона тяготения, " +
                                                        "'Нет' - для альтернативного закона (опровержения).",
                                                        "Выбор модели поведения", MessageBoxButtons.YesNo);
            

            if (dialogResult1 == DialogResult.Yes) //Ньютоновский закона тяготения
            {
                InitPlanets();
            }

            if (dialogResult1 == DialogResult.No) //альтернативный закон (опровержение)
            {
                Eros();
            }
        }

        private void Eros() //инициализация астреоида и зонда
        {
            MessageBox.Show("В середине февраля 2000 г. американцы подогнали космический зонд под названием NEAR " +
                "достаточно близко к астероиду Эрос, уравняли скорости и стали ждать захвата зонда тяготением Эроса, то есть " +
                "когда спутник мягко притянется тяготением астероида, но их попытки не оказались успешными. Астероид не притягивал к себе " +
                "американский зонд, а без подработки двигателем он вблизи Эроса не держался. Никакого притяжения между зондом массой 805 кг " +
                "и астероидом - около 6 трлн тон обнаружить не удалось.", "Гравитации не существует");

            ast = new Asteroid(Color.FromArgb(128, 128, 128), 300, 250);  //астероид 
            zn = new Zond(50, 100, 25);    //зонд
            timer3.Enabled = true;
        }

        private void InitPlanets() //инициализация параметров небесных тел для Ньютоновского закона
        {
            //Отображаем сообщение с запросом выбора способа ввода параметров небесных тел
            DialogResult dialogResult2 = MessageBox.Show("Выберите способ ввода параметров небесных тел: " +
                                                        "нажмите 'Да' для ввода параметров случайными числами, " +
                                                        "'Нет' - для ввода параметров вручную.",
                                                        "Выбор способа ввода", MessageBoxButtons.YesNo);

            if (dialogResult2 == DialogResult.Yes) //Случайные параметры
            {
                //радиус
                int rad1 = rnd.Next(10, 60);
                int rad2 = rnd.Next(10, 60);

                //длина
                int Height1 = rnd.Next(2 * rad1, this.Height / 5);
                int Height2 = rnd.Next(this.Height * 3 / 5, this.Height - 2 * rad2);

                //ширина
                int Width1 = rnd.Next(50, this.Width / 5);
                int Width2 = rnd.Next(this.Width * 2 / 3, this.Width - 2 * rad2);
            
                //изменение движения по x
                int dx = rnd.Next(10, 40);
                int dy = rnd.Next(10, 40);

                //параметры для цвета небесных тел
                int c1 = rnd.Next(0, 255);
                int c2 = rnd.Next(0, 255);
                int c3 = rnd.Next(0, 255);
                int c11 = rnd.Next(0, 255);
                int c22 = rnd.Next(0, 255);
                int c33 = rnd.Next(0, 255);

                pl1 = new Planet(rad1, Color.FromArgb(c1, c2, c3), Width1, Height1, dx, dy);  //первое тело
                pl2 = new Planet(rad2, Color.FromArgb(c11, c22, c33), Width2, Height2, dx, dy); //второе тело
                timer1.Enabled = true;
            }
            else if (dialogResult2 == DialogResult.No) //Ввод вручную
            {
                label1.Visible = true;

                System.Windows.Forms.TextBox textBox1 = new System.Windows.Forms.TextBox();
                textBox1.Top = label1.Bottom + 10; //расположение textBox ниже label
                textBox1.Left = 15; //расположение левого края textBox на одном уровне с label
                textBox1.AutoSize = true; //Устанавливаем автоматическое размещение и размер шрифта
                textBox1.Font = new Font("Arial Narrow", 14); //Увеличение шрифта

                this.Controls.Add(textBox1);

                textBox1.KeyDown += new KeyEventHandler(textBox1_KeyDown);
            }
        }//end InitPlanets

        private void Form1_KeyDown(object sender, KeyEventArgs e) //действия при нажатии клавиши ESC
        {
            if (e.KeyData == Keys.Escape)
            {
                using (Font font = new Font("Arial Narrow", 26))
                {
                    using (SolidBrush brush = new SolidBrush(Color.White))
                    {
                        g.DrawString("Игра завершена", font, brush, new PointF(200, 100)); //вывод сообщения о завершении игры
                    }
                }
                Thread.Sleep(800);
                this.Close();
            }
        }

        private void textBox1_KeyDown(object sender, KeyEventArgs e)
        {
            var textBox = sender as System.Windows.Forms.TextBox;
            if (textBox != null && e.KeyCode == Keys.Space)
            {
                try
                {
                    //Ввод пользователя разделен пробелами, считывается и конвертируется в число
                    int number = int.Parse(textBox.Text.Trim());
                    if (number > 0)
                    {
                        userParams.Add(number);
                        //Очищаем TextBox для ввода следующего числа
                        textBox.Text = "";
                    }
                    else
                    {
                        //Сообщение пользователю о некорректном вводе
                        MessageBox.Show("Некорректный формат ввода! Пожалуйста, введите положительное число.", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
                        //Сброс текста TextBox для повторного ввода
                        textBox.Text = "";
                    }
                }
                catch (FormatException)
                {
                    // Сообщение пользователю о некорректном вводе
                    MessageBox.Show("Некорректный формат ввода! Пожалуйста, введите целое число.", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    // Сброс текста TextBox для повторного ввода
                    textBox.Text = "";
                }
                
                if (userParams.Count >= 6) //Завершение ввода после ввода 7 чисел
                {
                    //Сообщение о корректном вводе
                    MessageBox.Show("Все данные приняты!", "Информация", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    textBox.Visible = false; //скрыть textBox2
                    label1.Visible = false;
                    
                    //радиус
                    int rad1 = userParams[0];
                    int rad2 = userParams[1];

                    //длина
                    int Height1 = rnd.Next(2 * rad1, this.Height / 5);
                    int Height2 = rnd.Next(this.Height * 3 / 5, this.Height - 2 * rad2);

                    //ширина
                    int Width1 = rnd.Next(0, this.Width / 5);
                    int Width2 = rnd.Next(this.Width * 2 / 3, this.Width - 2 * rad2);

                    //изменение движения по x
                    int dx = userParams[2];
                    int dy = userParams[2];

                    //массы тел
                    int m1 = userParams[3];
                    int m2 = userParams[4];
                    //расстояние между телами
                    int dist = userParams[5];

                    double gravconst = 6.67430E-11;
                    double F = gravconst * m1 * m2 / (dist^2);
                    //Расчет формулы
                    MessageBox.Show("F = G*m1*m2/r^2\nF = 6.67E-11*" +m1+ "*" +m2+ "/" + dist*dist + " = " +F+ "", "Ньютоновский закон тяготения", MessageBoxButtons.OK, MessageBoxIcon.Information);

                    pl1 = new Planet(rad1, Color.FromArgb(255, 255, 0), Width1, Height1, dx, dy); //первое тело
                    pl2 = new Planet(rad2, Color.FromArgb(30, 144, 255), Width2, Height2, dx, dy); //второе тело
                    timer1.Enabled = true;

                    userParams.Clear();
                    return;
                }//end if (userParams.Count >= 7)
            }//end if (textBox != null && e.KeyCode == Keys.Space)
        }//end textBox1_KeyDown

        private void label1_Click_1(object sender, EventArgs e)
        {

        }
    }//end Form1

    public class Asteroid : Form1 //класс Астероида
    {
        SolidBrush br;     // кисть для рисования астероида
        public int x { get; private set; }// координата x 
        public int y { get; private set; } // координата y

        public Asteroid(Color c, int x0, int y0) //конструктор
        {
            br = new SolidBrush(c);
            x = x0;
            y = y0;
        }

        public void Moving(Graphics g) //перемещение
        {
            g.Clear(Form1.BackC); //очистка формы
            x += 10;
            Draw(g);
        }

        public void Draw(Graphics g) //отрисовка астероида
        {
            g.FillEllipse(br, x, y, 200, 130);
        }
    }

    public class Zond : Form1 //класс Зонда
    {
        public int x { get; private set; }// координата x 
        public int y { get; private set; } // координата y

        public int dx { get; set; } // смещение

        public Zond(int x0, int y0, int dx0) //конструктор
        {
            x = x0;
            y = y0;
            dx = dx0;
        }

        public void Moving(Graphics g) //перемещение
        {
            g.Clear(Form1.BackC); //очистка формы
            x += dx;
            Draw(g);
        }

        public void Draw(Graphics g) //отрисовка зонда
        {
            image = Properties.Resources.sat; //изображение спутника
            g.DrawImage(image, x, y, 150, 100);
        }
    }

    public class Planet : Form1 //класс Планеты
    {
        public int rad { get; private set; }// радиус
        SolidBrush br;     // кисть для рисования планеты
        public int x { get; private set; }// координата x 
        public int y { get; private set; } // координата y
        public int dx { get; private set; } // шаг смещения по x
        public int dy { get; private set; } // шаг смещения по y

        public Planet(int r, Color c, int x0, int y0, int d_x, int d_y) //конструктор
        {
            rad = r;
            br = new SolidBrush(c);
            x = x0;
            y = y0;
            dx = d_x;
            dy = d_y;
        }

        public void Moving(Graphics g) //перемещение
        {
            g.Clear(Form1.BackC); //очистка формы
            Draw(g);
        }

        public void Draw(Graphics g) //отрисовка планеты
        {
            g.FillEllipse(br, x, y, 2 * rad, 2 * rad);
        }

        public void Chase(Planet target) //расчет траектории движения планеты
        {
            // Вычисляем расстояние между планетами
            int distanceX = target.x - x;
            int distanceY = target.y - y;

            // Вычисляем угол между планетами
            double angle = Math.Atan2(distanceY, distanceX);

            // Вычисляем новые координаты планеты
            x += (int)(Math.Cos(angle) * dx);
            y += (int)(Math.Sin(angle) * dy);
        }
    }//end Planet
}//end namespace Course_paper