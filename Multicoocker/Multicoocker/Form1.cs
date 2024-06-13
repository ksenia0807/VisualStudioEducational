using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Multicoocker
{
    public partial class Form1 : Form
    {
        public System.Drawing.Image image;  //класс изображения
        Graphics g;                         //окно
        static public Color BackC = Color.FromArgb(255, 255, 255);  //цвет окна
        public int[] userParams = new int[4];

        public Form1()
        {
            InitializeComponent();
            this.BackColor = BackC; //установка цвета окна
            this.Width = 900;       //длина окна
            this.Height = 600;      //ширина окна
            this.DoubleBuffered = true; //форма сохраняет содержание

            Button btn1 = new Button();
            btn1.Location = new Point(100, 100);
            btn1.Text = "Ручной";
            btn1.Size = new Size(100, 50);
            btn1.Click += new EventHandler(btn1_Click);
            Controls.Add(btn1);

            Button btn2 = new Button();
            btn2.Location = new Point(400, 100);
            btn2.Text = "Не ручной";
            btn2.Size = new Size(100, 50);
            btn2.Click += new EventHandler(btn2_Click);
            Controls.Add(btn2);

        }

        private void btn1_Click(object btn1, EventArgs e)
        {
            // Очистить форму
            Controls.Clear();

            Label warning = new Label();        //предупреждение о вводе времени и температуры. после каждого ввода ОБЯЗАТЕЛЬНО нажимать ENTER
            warning.Text = "После каждого ввода нажать клавишу ENTER!!!";
            warning.Location = new System.Drawing.Point(50, 50);
            warning.AutoSize = true;
            warning.Font = new Font("Arial Narrow", 12);
            warning.ForeColor = Color.Red;
            Controls.Add(warning);

            Label timeLabel = new Label();
            timeLabel.Text = "Введите время готовки";
            timeLabel.Location = new System.Drawing.Point(50, 150);
            timeLabel.AutoSize = true;
            timeLabel.Font = new Font("Arial Narrow", 14);
            Controls.Add(timeLabel);

            System.Windows.Forms.TextBox textBox11 = new System.Windows.Forms.TextBox();
            textBox11.Location = new System.Drawing.Point(300, 150);
            textBox11.AutoSize = true; //Устанавливаем автоматическое размещение и размер шрифта
            textBox11.Width = 30;
            textBox11.TextAlign = HorizontalAlignment.Center;
            textBox11.Font = new Font("Arial Narrow", 14); //Увеличение шрифта
            this.Controls.Add(textBox11);
            textBox11.KeyDown += new KeyEventHandler(hFormat);

            Label h = new Label();
            h.Text = "ч";
            h.Location = new System.Drawing.Point(300+35, 150);
            h.AutoSize = true;
            h.Font = new Font("Arial Narrow", 14);
            Controls.Add(h);

            Label doublepoint = new Label();
            doublepoint.Text = ":";
            doublepoint.Location = new System.Drawing.Point(300+50, 140);
            doublepoint.AutoSize = true;
            doublepoint.Font = new Font("Arial Narrow", 30);
            Controls.Add(doublepoint);

            System.Windows.Forms.TextBox textBox12 = new System.Windows.Forms.TextBox();
            textBox12.Location = new System.Drawing.Point(380, 150);
            textBox12.AutoSize = true; //Устанавливаем автоматическое размещение и размер шрифта
            textBox12.Width = 30;
            textBox12.TextAlign = HorizontalAlignment.Center;
            textBox12.Font = new Font("Arial Narrow", 14); //Увеличение шрифта
            this.Controls.Add(textBox12);
            textBox12.KeyDown += new KeyEventHandler(mFormat);

            Label m = new Label();
            m.Text = "м";
            m.Location = new System.Drawing.Point(380 + 35, 150);
            m.AutoSize = true;
            m.Font = new Font("Arial Narrow", 14);
            Controls.Add(m);

            Label doublepoint2 = new Label();
            doublepoint2.Text = ":";
            doublepoint2.Location = new System.Drawing.Point(380 + 50, 140);
            doublepoint2.AutoSize = true;
            doublepoint2.Font = new Font("Arial Narrow", 30);
            Controls.Add(doublepoint2);

            System.Windows.Forms.TextBox textBox13 = new System.Windows.Forms.TextBox();
            textBox13.Location = new System.Drawing.Point(460, 150);
            textBox13.AutoSize = true; //Устанавливаем автоматическое размещение и размер шрифта
            textBox13.Width = 30;
            textBox13.TextAlign = HorizontalAlignment.Center;
            textBox13.Font = new Font("Arial Narrow", 14); //Увеличение шрифта
            this.Controls.Add(textBox13);
            textBox13.KeyDown += new KeyEventHandler(sFormat);

            Label s = new Label();
            s.Text = "с";
            s.Location = new System.Drawing.Point(460 + 35, 150);
            s.AutoSize = true;
            s.Font = new Font("Arial Narrow", 14);
            Controls.Add(s);

            // Ввод температуры 
            Label temperatureLabel = new Label();
            temperatureLabel.Text = "Введите температуру готовки";
            temperatureLabel.Location = new System.Drawing.Point(50, 250);
            temperatureLabel.AutoSize = true;
            temperatureLabel.Font = new Font("Arial Narrow", 14);
            Controls.Add(temperatureLabel);

            System.Windows.Forms.TextBox textBox2 = new System.Windows.Forms.TextBox();
            textBox2.Location = new System.Drawing.Point(300, 250);
            textBox2.AutoSize = true; //Устанавливаем автоматическое размещение и размер шрифта
            textBox2.Width = 80;
            textBox2.TextAlign = HorizontalAlignment.Center;
            textBox2.Font = new Font("Arial Narrow", 14); //Увеличение шрифта
            this.Controls.Add(textBox2);
            textBox2.KeyDown += new KeyEventHandler(tFormat);

            Button ready = new Button();
            ready.Location = new Point(600, 300);
            ready.Text = "Готово";
            ready.Click += (sender, ev) => ready_Click(sender, e, userParams);
            Controls.Add(ready);


        }

        private void hFormat(object sender, KeyEventArgs e)
        {
            int hour = 0;
            var textBox = sender as System.Windows.Forms.TextBox;
            if (textBox != null && e.KeyCode == Keys.Enter)
            {
                try
                {
                    //Ввод пользователя разделен пробелами, считывается и конвертируется в число
                    int number = int.Parse(textBox.Text);
                    if ((number >= 0) && (number <= 23))
                    {
                        hour = number;
                        userParams[0] = hour;
                    }
                    else
                    {
                        //Сообщение пользователю о некорректном вводе
                        MessageBox.Show("Некорректный формат ввода! Пожалуйста, введите число от 0 до 23.", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
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
            }//end if 
            
        }//end 

        private void mFormat(object sender, KeyEventArgs e)
        {
            int minute = 0;
            var textBox = sender as System.Windows.Forms.TextBox;
            if (textBox != null && e.KeyCode == Keys.Enter)
            {
                try
                {
                    //Ввод пользователя разделен пробелами, считывается и конвертируется в число
                    int number = int.Parse(textBox.Text);
                    if ((number >= 0) && (number <= 59))
                    {
                        minute = number;
                        userParams[1] = minute;
                    }                    
                    else
                    {
                        //Сообщение пользователю о некорректном вводе
                        MessageBox.Show("Некорректный формат ввода! Пожалуйста, введите число от 0 до 59.", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
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
            }//end if 
            
        }//end 

        private void sFormat(object sender, KeyEventArgs e)
        {
            int sec = 0;
            var textBox = sender as System.Windows.Forms.TextBox;
            if (textBox != null && e.KeyCode == Keys.Enter)
            {
                try
                {
                    //Ввод пользователя разделен пробелами, считывается и конвертируется в число
                    int number = int.Parse(textBox.Text);
                    if ((number >= 0) && (number <= 59))
                    {
                        sec = number;
                        userParams[2] = sec;
                    }
                    else
                    {
                        //Сообщение пользователю о некорректном вводе
                        MessageBox.Show("Некорректный формат ввода! Пожалуйста, введите число от 0 до 59.", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
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
            }//end if 
            
        }//end 

        private void tFormat(object sender, KeyEventArgs e)
        {
            var textBox = sender as System.Windows.Forms.TextBox;
            //if (textBox != null && e.KeyCode == Keys.Enter)
            //{
                //try
                //{
                    //Ввод пользователя разделен пробелами, считывается и конвертируется в число
                    int number = Convert.ToInt32(textBox.Text);
                    if ((number >= 30) && (number <= 240))
                    {
                        int temp = number;
                        Console.WriteLine(temp);
                        userParams[3] = temp;
                    }
                    else
                    {
                        //Сообщение пользователю о некорректном вводе
                        MessageBox.Show("Некорректный формат ввода! Пожалуйста, введите число от 30 до 240.", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
                        //Сброс текста TextBox для повторного ввода
                        textBox.Text = "";
                    }
                //}
                //catch (FormatException)
                //{
                //    // Сообщение пользователю о некорректном вводе
                //    MessageBox.Show("Некорректный формат ввода! Пожалуйста, введите целое число.", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
                //    // Сброс текста TextBox для повторного ввода
                //    textBox.Text = "";
                //}
            }//end if 
        }//end 

        public void ready_Click(object btn2, EventArgs e, int[] userParams)
        {
            int z = 0;
            int y = 0;
            for (int i = 0; i < 4; i++)
            {
                Console.WriteLine(userParams[i]);
                z += userParams[i];
            }
            if (z == 0)
            {
                MessageBox.Show("Некорректный формат ввода! Пожалуйста, введите время и температуру.", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            if (userParams[3] == 0)
            {
                MessageBox.Show("Некорректный формат ввода! Пожалуйста, введите температуру.", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            for (int i = 0; i < 3; i++)
            {
                Console.WriteLine(userParams[i]);
                y += userParams[i];
            }
            if (y == 0)
            {
                MessageBox.Show("Некорректный формат ввода! Пожалуйста, введите время.", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }

            Controls.Clear();
            Label preparing1Label = new Label();
            preparing1Label.Text = "Еда готовится";
            preparing1Label.Location = new System.Drawing.Point(50, 250);
            preparing1Label.AutoSize = true;
            Controls.Add(preparing1Label);
        }

        private void btn2_Click(object btn2, EventArgs e)
        {
            // Очистить форму
            Controls.Clear();
            int size = 15;
            Button[] buttons = new Button[size];

            // Создать новую кнопку
            string[] name = new string[size];
            name[0] = "Макароны";
            name[1] = "Варка";
            name[2] = "Каша";
            name[3] = "Суп";
            name[4] = "На пару";
            name[5] = "Разморозка";
            name[6] = "Йогурт";
            name[7] = "Жарка";
            name[8] = "Выпечка";
            name[9] = "Крупа";
            name[10] = "Тушение";
            name[11] = "Хлеб";
            name[12] = "Компот";
            name[13] = "Рыба";
            name[14] = "Холодец";

            // Добавить новую кнопку на форму
            for(int i=0;i<size;i++)
            {
                buttons[i] = new Button(); // Создание новой кнопки

                int shirina =100;
                int vysota = 100;

                if ((i % 5) == 0)
                {
                    shirina = 100;
                    vysota = 100+i/5*50;
                }else if ((i%5)<5)
                {
                    shirina = 100+i%5*100;
                    vysota = 100 + i / 5 * 50;
                }
                
                buttons[i].Location = new Point(shirina, vysota);
                buttons[i].Text = name[i];
                buttons[i].Size = new Size(100, 50);

                Controls.Add(buttons[i]);
            }
        }
    }
}
