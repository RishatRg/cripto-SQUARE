

#include "SQUARE.h"
void  main()
{
	setlocale(LC_ALL, "");
	
	ifstream Text("picture.jpg", ios::binary); // ���������� �� ���� 
	ifstream key("key.bin", ios::binary);
	ofstream out("out.jpg",ios::binary);
	ifstream in2("in2.bin", ios::binary);	// ���������� ���� ������������� ������, ��� �� ������������ �� ���� ��� ����������� 
	ofstream sign("���.bin", ios::binary);
	ofstream hesh("hesh.bin", ios::binary);
	ofstream hesh1("hesh1.bin", ios::binary);
	
	int x;
	cout << " ������� '1' ��� ���������� � '2' ��� ����������� ����� : ";
	cin >> x;
	if (x == 1)
	{
		square a(Text, key);    		
		a.Encryption_mode(Text);//// ������������� ������ � ����������� ���� � ����������� �������
		ofstream out2("in2.bin", ios::binary);
		a.show_sign(sign);
		a.hesh_show(hesh);
		a.database_show(out);	  //// ������� �������������� ����� � ���� out.txt
		a.database_show(out2);
		out.close();
	}
	else 
		{
		square b(in2, key);
		b.Decryption_mode(in2);	  //// �������������� ������ 
		b.database_show(out);	  //// ������� �������������� ������
		b.hesh_show(hesh1);
		out.close();
		}

	system("pause");
}

