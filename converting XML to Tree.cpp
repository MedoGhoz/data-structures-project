string sys_std(String^ s) {
	if (s == nullptr) { return ""; }
	string res = msclr::interop::marshal_as<string>(s);
	return res;
}

String^ std_sys(string s) {
	String^ res;
	res = msclr::interop::marshal_as<String^>(s);
	return res;
}

string getTag(string s) {
	int i = 1;
	int start = 1;
	string res;
	while (s[i] != '>') {
		if (s[i] == '/') {
			start = 2;
		}
		i++;
	}
	res = s.substr(start, i - start);
	return res;
}

string getTag2(string s) {
	int i = 1;
	while (s[i] != '<') {
		i++;
		if (i == s.size()) { i = -1; break; }
	}
	if (i == -1) { return "     "; }
	string res = s.substr(i, s.size() - i);
	return "</" + getTag(res) + ">";
}

string getData(string s, int n) {
	s = s.substr(n + 2, s.size() - n);
	int i = 0;
	while (s[i] != '<') {
		i++;
		if (i == s.size()) { i = -1; break; }
	}
	if (i == -1) { return s; }
	string res = s.substr(0, i);
	return res;
}

string removeSpaces(string s) {
	int i = 0;
	while (s[i] == ' ') {
		i++;
	}
	if (i == 0) { return s; }
	return s.substr(i, s.size() - 1);
}

TreeNode getTreeNode(StreamReader^ xmlfile) {

	TreeNode theFile("the file", "", 0);

	string in;
	String^ inn;

	vector<TreeNode> vec;
	vec.push_back(theFile);
	int ii = 0;        // used to know the current parent (usually the size of vec -1 )
	int i = 0;         // just for debugging ... no meaning
	int theCase = 1;   // 1 for normal line or only the tag  // not 1 for line that contain the tag anf its end
					   // 2 for reading the data ....... 3 for reading the end tag
	string temp = "";  // used in case 2 and 3
	string temp2 = ""; // used in case 2 and 3
	while (true) {
		i++;
		if (i == 3) {
			i = 3; // just for debugging ... no meaning
		}


		switch (theCase)
		{
		case 1:
			inn = xmlfile->ReadLine();
			in = sys_std(inn);
			in = removeSpaces(in);
			break;

		case 2:
			temp2 = in;
			in = temp;
			theCase = 3;
			break;

		case 3:
			in = getTag2(temp2);
			theCase = 1;
			break;
		}


		if (in[0] == '<' && in[1] != '/') { //new tag
			string s;
			s = getTag(in);
			//TreeNode* node = new TreeNode(s, "no", vec[ii].getlevel() + 1);
			TreeNode node(s, "", vec[ii].getlevel() + 1);
			vec.push_back(node);
			ii++;

			if (in.size() - s.size() == 2) {
				theCase = 1;
			}
			else {
				theCase = 2;
				temp = getData(in, s.size());
			}


		}

		else {
			if (in[0] == '<' && in[1] == '/') {//ending tag
				ii--;
				vec[ii].addChild_(vec[ii + 1]);
				vec.erase(vec.begin() + ii + 1);
			}
			else {//contain
				if (in != "     ") {
					vec[ii].setContain(in);
				}
			}
		}

		if (in == "") {
			break;
		}

	}
	TreeNode res = vec[0];
	res.children_to_children();


	return res;
}
