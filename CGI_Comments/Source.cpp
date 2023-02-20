#include <iostream>
#include <fstream>
using namespace std;

const char* TITLE = "Обратная связь";
const char* HEADER = "Оставьте Ваш комментарий";
void load_content(const char* template_name);

char* get_menu(const char* menu_filename)
{
	ifstream mf(menu_filename);
	const size_t res_sz = 65535;
	char* res = new char[res_sz];
	res[0] = 0;
	if (mf.is_open())
	{
		char* menuline = new char[1024];
		while(!mf.eof())
		{
			mf.getline(menuline, 1024);
			char* title;
			char* page = strtok_s(menuline, " ", &title);
			strcat_s(res, res_sz, "<div class='menuitem'>");
			strcat_s(res, res_sz, "<a href='");
			strcat_s(res, res_sz, page);
			strcat_s(res, res_sz, "'>");
			strcat_s(res, res_sz, title);
			strcat_s(res, res_sz, "</a></div>\n");
		}
		delete[] menuline;
		mf.close();
	}
	return res;
}

char* parse(const char* buf)
{
	char* res;
	if (!strcmp(buf, "<!--title-->"))
	{
		res = new char[strlen(TITLE) + 1];
		strcpy_s(res, strlen(TITLE) + 1, TITLE);
	} else if (!strcmp(buf, "<!--header-->"))
	{
		res = new char[strlen(HEADER) + 1];
		strcpy_s(res, strlen(HEADER) + 1, HEADER);
	} else if (!strcmp(buf, "<!--menu-->"))
	{
		res = get_menu("menu.txt");
	} else if (!strcmp(buf, "<!--content-->"))
	{
		load_content("form.htm");
		res = (char*)"";
	} else
	{
		res = new char[strlen(buf) + 1];
		strcpy_s(res, strlen(buf) + 1, buf);
	}
	return res;
}

void load_content(const char* template_name)
{
	ifstream tf(template_name);
	if (tf.is_open())
	{
		const size_t buf_sz = 65535;
		char* buf = new char[buf_sz];
		while (!tf.eof())
		{
			tf.getline(buf, buf_sz);
			char* parsed_buf = parse(buf);
			cout << parsed_buf << endl;
			delete[] parsed_buf;
		}
		delete[] buf;
		tf.close();
	}
}

void main()
{
	cout << "Content-type: text/html; charset=windows-1251\n\n";
	load_content("template");
}