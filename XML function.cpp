void xml(TreeNode* node, StreamWriter^ tree_xml) {
		String^ xx;

		string sp = "";
		for (int i = node->getlevel(); i > 0; i--) {
			sp += "   ";
		}
		sp += "<" + node->getData() + ">";
		if (node->getContain() != "") {
			sp += node->getContain();
		}
		else {

			xx = std_sys(sp);
			tree_xml->WriteLine(xx);
			sp = "";
		}
		if (node->getChildern().size() == 0) {
			sp += "<\/" + node->getData() + ">";
			xx = std_sys(sp);
			tree_xml->WriteLine(xx);
			sp = "";
			return;
		}
		else {
			for (int i = 0; i < node->getChildern().size(); i++) {
				xml((node->getChildern())[i], tree_xml);
			}
		}
		for (int i = node->getlevel(); i > 0; i--) {
			sp += "   ";
		}
		sp += "<\/" + node->getData() + ">";
		xx = std_sys(sp);
		tree_xml->WriteLine(xx);

	}
