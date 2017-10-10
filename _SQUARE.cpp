

#include "SQUARE.h"
void  main()
{
	setlocale(LC_ALL, "");
	
	ifstream data("picture.jpg", ios::binary); // отправляем на вход 
	ifstream key("key.bin", ios::binary);
	ofstream out("out.jpg",ios::binary);
	ifstream in2("in2.bin", ios::binary);
	ofstream sign("ЭЦП.bin", ios::binary);
	ofstream hesh("hesh.bin", ios::binary);
	ofstream hesh1("hesh1.bin", ios::binary);
	
	int x;
	cin >> x;
	if (x == 1)
	{
		square a(data, key);      //// Создаем класс			
		a.Encryption_mode(Text);//// зашифровывает текст с добавление хеша и подписи в режиме шифрования 
		ofstream out2("in2.bin", ios::binary);
		a.show_sign(sign);
		a.hesh_show(hesh);
		a.database_show(out);	  //// выводим зашифрованнный текст в файл out.txt
		a.database_show(out2);
		out.close();
	}
	else 
		{
		
		square b(in2, key);
		b.Decryption_mode(in2);	  //// дешифруем текст 
		b.database_show(out);	  //// выводим расшифрованный текст 
		b.hesh_show(hesh1);
		out.close();
		}

	system("pause");
}

