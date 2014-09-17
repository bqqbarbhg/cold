#include "ast.h"
#include <iostream>
#include <ostream>
#include <fstream>
#include <sstream>

namespace cold { namespace script {

AstStatementList::~AstStatementList() {
	for (std::vector<AstNode*>::iterator it = nodes.begin(); it != nodes.end(); ++it)
		delete *it;
}
std::string AstStatementList::repr() const {
	std::stringstream s(std::ios::out);
	for (std::vector<AstNode*>::const_iterator it = nodes.cbegin(); it != nodes.cend(); ++it)
		s << (*it)->repr() << "\n";
	return s.str();
}
AstAssign::AstAssign(AstNode *d, AstNode *s)
	: src(s), dst(d)
{
}
AstAssign::~AstAssign() {
	delete src;
	delete dst;
}
std::string AstAssign::repr() const {
	std::stringstream s(std::ios::out);
	s << dst->repr() << " = " << src->repr();
	return s.str();
}

AstIdentifier::AstIdentifier(const std::string& s)
	: name(s)
{
}
std::string AstIdentifier::repr() const {
	return name;
}

AstCall::AstCall(AstNode* n, const std::vector<AstNode*>& p) 
	: node(n), params(p)
{
}
AstCall::~AstCall() {
	delete node;
	for (std::vector<AstNode*>::iterator it = params.begin(); it != params.end(); ++it)
		delete *it;
}
std::string AstCall::repr() const {
	std::stringstream s(std::ios::out);
	s << node->repr() << "(";
	for (std::vector<AstNode*>::const_iterator it = params.cbegin(); it != params.cend(); ++it) {
		s << (*it)->repr();
		if (it + 1 != params.cend())
			s << ", ";
	}
	s << ")";
	return s.str();
}

AstConstant::AstConstant(Type t, const char *begin, const char *end)
	: type(t)
{
	switch (t) {
	case INT:
		value._int = 0;
		while (begin != end)
			value._int = value._int * 10 + (*begin++ - '0');
		break;
	}
}

std::string AstConstant::repr() const {
	std::stringstream s(std::ios::out);
	switch (type) {
	case INT:
		s << value._int;
	}
	return s.str();
}

AstBinOp::AstBinOp(Token::Type t, AstNode *l, AstNode *r)
	: type(t), left(l), right(r)
{
}
AstBinOp::~AstBinOp() {
	delete left;
	delete right;
}

std::string AstBinOp::repr() const {
	std::stringstream s(std::ios::out);
	s << left->repr();
	switch (type) {
	case Token::ADD: s << " + "; break;
	case Token::SUB: s << " - "; break;
	case Token::MUL: s << " * "; break;
	case Token::DIV: s << " / "; break;
	case Token::MOD: s << " % "; break;
	case Token::OPEN_BRACKET: s << "["; break;
	case Token::DOT: s << "."; break;
	}
	s << right->repr();
	if (type == Token::OPEN_BRACKET)
		s << "]";
	return s.str();
}


AstUnaryOp::AstUnaryOp(Token::Type t, AstNode *n)
	: type(t), node(n)
{
}
AstUnaryOp::~AstUnaryOp() {
	delete node;
}
std::string AstUnaryOp::repr() const {
	std::stringstream s(std::ios::out);
	switch (type) {
	case Token::ADD: s << " + "; break;
	case Token::SUB: s << " - "; break;
	}
	s << node->repr();
	return s.str();
}
AstTernaryOp::AstTernaryOp(AstNode *c, AstNode *t, AstNode *f)
	: cond(c), true_node(t), false_node(f)
{
}
AstTernaryOp::~AstTernaryOp() {
	delete cond;
	delete true_node;
	delete false_node;
}
std::string AstTernaryOp::repr() const {
	std::stringstream s(std::ios::out);
	s << cond->repr() << " ? " << true_node->repr() << " : " << false_node->repr();
	return s.str();
}

AstMember::AstMember(AstNode *n, const std::string& s)
	: node(n), name(s)
{
}
AstMember::~AstMember() {
	delete node;
}
std::string AstMember::repr() const {
	return node->repr() + "." + name;
}

AstLambda::AstLambda(const std::vector<Param>& p, AstNode *b)
	: params(p), body(b)
{
}
AstLambda::~AstLambda() {
	delete body;
}
std::string AstLambda::repr() const {
	std::stringstream s(std::ios::out);
	s << "(";
	for (std::vector<Param>::const_iterator it = params.cbegin(); it != params.cend(); ++it) {
		s << it->repr();
		if (it + 1 != params.cend())
			s << ", ";
	}
	s << ") => " << body->repr();
	return s.str();
}

AstTuple::AstTuple(const std::vector<AstNode*>& n)
	: nodes(n)
{
}
AstTuple::~AstTuple() {
	for (std::vector<AstNode*>::iterator it = nodes.begin(); it != nodes.end(); ++it)
		delete *it;
}
std::string AstTuple::repr() const {
	std::stringstream s(std::ios::out);
	s << "(";
	for (std::vector<AstNode*>::const_iterator it = nodes.cbegin(); it != nodes.cend(); ++it) {
		s << (*it)->repr();
		if (it + 1 != nodes.cend())
			s << ", ";
	}
	s << ")";
	return s.str();
}

bool AstNode::get_params(std::vector<Param>& p) const {
	Param q;
	if (get_param(q)) return true;
	p.push_back(q);
	return false;
}
bool AstNode::get_param(Param& p) const {
	return true;
}
bool AstIdentifier::get_param(Param& p) const {
	p.name = name;
	return false;
}
bool AstTuple::get_params(std::vector<Param>& p) const {
	Param q;
	for (std::vector<AstNode*>::const_iterator it = nodes.begin(); it != nodes.end(); ++it) {
		if ((*it)->get_param(q)) return true;
		p.push_back(q);
	}
	return false;
}

} }