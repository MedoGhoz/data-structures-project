	
	class TreeNode {
		string data;
		string contain;
		vector<TreeNode*> childern;
		vector<TreeNode> childern_;
		int level;
	public:
		TreeNode(string data, string contain, int level) {
			this->data = data;
			this->level = level;
			this->contain = contain;
		}
		void addChild(TreeNode* child) {
			childern.push_back(child);
		}
		void addChild_(TreeNode child) {
			childern_.push_back(child);
		}
		vector<TreeNode*> getChildern() {
			return childern;
		}
		int getlevel() {
			return level;
		}
		string getData() {
			return data;
		}
		string getContain() {
			return contain;
		}
		void setContain(string s) {
			contain = s;
		}
		void children_to_children() {
			for (int i = 0; i < childern_.size(); i++) {
				addChild(&childern_[i]);
				childern_[i].children_to_children();
			}
		}
	};

	class tree {
		TreeNode* root;
	public:
		int level;
		tree() {
			level = 0;
		}
		tree(TreeNode* root) {
			this->root = root;
			level = 0;
		}
		void setroot(TreeNode* r) {
			root = r;
		}
		TreeNode* getroot() {
			return root;
		}
		bool empty() {
			if (root == NULL) {
				return true;
			}
			return false;
		}
	};
	
void XML_to_JSON_converter(TreeNode* node, vector<TreeNode*> parent_children, int child_number, StreamWriter^ JSON) {
		
		string sp = "";

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////non leaf node////////////////////////////////////////////////
		if (node->getChildern().size() != 0) {
			if (parent_children.size() == 0) {////////////////////////////////////////root
				//cout << "{" << endl << "\"" << node->getData() << "\": {" << endl;
				JSON->WriteLine(std_sys("{"));
				sp = "\"" + node->getData() + "\": {";
				JSON->WriteLine(std_sys(sp));

				for (int i = 0; i < node->getChildern().size(); i++) {
					XML_to_JSON_converter((node->getChildern())[i], node->getChildern(), i, JSON);
				}
				//cout << endl << "}";
				//cout << endl << "}";	
				JSON->WriteLine(std_sys(""));							
				JSON->WriteLine(std_sys("}"));
				JSON->Write(std_sys("}"));
				return;
			}
			else if (parent_children.size() == 1) {////////////////////////////////only one node
				//cout << "\"" << node->getData() << "\": {" << endl;
				sp = "\"" + node->getData() + "\": {";
				JSON->WriteLine(std_sys(sp));
				for (int i = 0; i < node->getChildern().size(); i++) {
					XML_to_JSON_converter((node->getChildern())[i], node->getChildern(), i, JSON);
				}
				//cout << endl << "}";
				JSON->WriteLine(std_sys(""));
				JSON->Write(std_sys("}"));
				return;
			}
			else {/////////////////////////////////////////////////////////////////non root with more than one node
				if (child_number + 1 < parent_children.size()) {//////there is a node after me
					if (child_number == 0) {
						if (parent_children[child_number]->getData() == parent_children[child_number + 1]->getData()) {
							//cout << "\"" << node->getData() << "\": [" << endl << "{" << endl;
							sp = "\"" + node->getData() + "\": [";
							JSON->WriteLine(std_sys(sp));
							JSON->WriteLine(std_sys("{"));
						}
						else {
							//cout << "\"" << node->getData() << "\": {" << endl;
							sp = "\"" + node->getData() + "\": {";
							JSON->WriteLine(std_sys(sp));
						}
					}
					else {
						if (parent_children[child_number]->getData() == parent_children[child_number - 1]->getData()) {
							//cout << "{" << endl;
							JSON->WriteLine(std_sys("{"));
						}
						else {
							if (parent_children[child_number]->getData() == parent_children[child_number + 1]->getData()) {
								//cout << "\"" << node->getData() << "\": [" << endl << "{" << endl;
								sp = "\"" + node->getData() + "\": [";
								JSON->WriteLine(std_sys(sp));
								JSON->WriteLine(std_sys("{"));
							}
							else {
								//cout << "\"" << node->getData() << "\": {" << endl;
								sp = "\"" + node->getData() + "\": {";
								JSON->WriteLine(std_sys(sp));
							}
						}

					}
					for (int i = 0; i < node->getChildern().size(); i++) {
						XML_to_JSON_converter((node->getChildern())[i], node->getChildern(), i, JSON);
					}
					//cout << endl << "}," << endl;
					JSON->WriteLine(std_sys(""));
					JSON->WriteLine(std_sys("},"));

					if (child_number != 0) {
						if (parent_children[child_number]->getData() == parent_children[child_number - 1]->getData()) {
							if (parent_children[child_number]->getData() != parent_children[child_number + 1]->getData()) {
								//cout << endl << "]," << endl;
								JSON->WriteLine(std_sys(""));
								JSON->WriteLine(std_sys("],"));
							}
						}
					}
				}
				else {///////////////////////////////////////////////I'm the last node
					if (parent_children[child_number]->getData() == parent_children[child_number - 1]->getData()) {
						//cout << "{";
						JSON->Write(std_sys("{"));
					}
					else {
						//cout << "\"" << node->getData() << "\": {" << endl;
						sp = "\"" + node->getData() + "\": {";
						JSON->WriteLine(std_sys(sp));
					}
					for (int i = 0; i < node->getChildern().size(); i++) {
						XML_to_JSON_converter((node->getChildern())[i], node->getChildern(), i, JSON);
					}
					//cout << endl << "}";
					JSON->WriteLine(std_sys(""));
					JSON->Write(std_sys("}"));
					if (child_number != 0) {
						if (parent_children[child_number]->getData() == parent_children[child_number - 1]->getData()) {
							//cout << endl << "]";
							JSON->WriteLine(std_sys(""));
							JSON->Write(std_sys("]"));
						}
					}
				}
			}

		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////leaf node/////////////////////////////////////////////////////////////
		else {
			if (child_number + 1 < parent_children.size()) {////////////there is a node after me
				if (child_number == 0) {
					//cout << "\"" << node->getData() << "\" :";
					sp = "\"" + node->getData() + "\" :";
					JSON->Write(std_sys(sp));
					if (parent_children[child_number]->getData() == parent_children[child_number + 1]->getData()) {
						//cout << "[" << endl << "\"" << node->getContain() << "\"," << endl;
						JSON->WriteLine(std_sys("["));
						sp = "\"" + node->getContain() + "\",";
						JSON->WriteLine(std_sys(sp));
						return;
					}
					else {
						//cout << "\"" << node->getContain() << "\"" << "," << endl;
						sp = "\"" + node->getContain() + "\"" + ",";
						JSON->WriteLine(std_sys(sp));
						return;
					}
				}
				else {
					if (parent_children[child_number]->getData() == parent_children[child_number - 1]->getData()) {
						if (parent_children[child_number]->getData() != parent_children[child_number + 1]->getData()) {
							//cout << "," << endl << "\"" << node->getContain() << "\" " << endl << "]," << endl;
							JSON->WriteLine(std_sys(","));
							sp = "\"" + node->getContain() + "\" ";
							JSON->WriteLine(std_sys(sp));
							JSON->WriteLine(std_sys("],"));
							return;
						}
						else {
							//cout << "," << endl << "\"" << node->getContain() << "\"";
							JSON->WriteLine(std_sys(","));
							sp = "\"" + node->getContain() + "\"";
							JSON->Write(std_sys(sp));
							return;
						}
					}
					else {
						if (parent_children[child_number]->getData() == parent_children[child_number + 1]->getData()) {
							//cout << "\"" << node->getData() << "\" :";
							//cout << "[" << endl << "\"" << node->getContain() << "\"";
							sp = "\"" + node->getData() + "\" :" + "[";
							JSON->WriteLine(std_sys(sp));
							sp = "\"" + node->getContain() + "\"";
							JSON->Write(std_sys(sp));
							return;
						}
						else {
							//cout << "\"" << node->getData() << "\" :";
							//cout << "\"" << node->getContain() << "\"" << "," << endl;
							sp = "\"" + node->getData() + "\" :" + "\"" + node->getContain() + "\"" + ",";
							JSON->WriteLine(std_sys(sp));							
							return;
						}
					}
				}
			}
			else {///////////////////////////////////////////////////////I'm the last node
				if (child_number != 0) {
					if (parent_children[child_number]->getData() == parent_children[child_number - 1]->getData()) {
						//cout << "\"" << node->getContain() << "\" " << endl << "]";
						sp = "\"" + node->getContain() + "\" ";
						JSON->WriteLine(std_sys(sp));
						JSON->Write(std_sys("]"));
						return;
					}
					else {
						//cout << "\"" << node->getData() << "\" :";
						//cout << "\"" << node->getContain() << "\"";
						sp = "\"" + node->getData() + "\" :" + "\"" + node->getContain() + "\"";
						JSON->Write(std_sys(sp));
						return;
					}
				}
				else {
					//cout << "\"" << node->getData() << "\" :";
					//cout << "\"" << node->getContain() << "\"";
					sp = "\"" + node->getData() + "\" :" + "\"" + node->getContain() + "\"";
					JSON->Write(std_sys(sp));
					return;
				}
			}

		}
	}