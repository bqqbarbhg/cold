#ifndef _COLD_SCRIPT_COMPILE_AST_H
#define _COLD_SCRIPT_COMPILE_AST_H

#include <vector>
#include <cold/script/compile/token.h>
#include <cold/script/param.h>
#include <string>

namespace cold { namespace script {

class Compiler;
struct Value;

struct AstNode {
	virtual ~AstNode() { }
	virtual std::string repr() const = 0;
	virtual bool emit(Compiler& c) const = 0;
	virtual bool emit_lvalue(Compiler& c) const;
	virtual bool get_params(std::vector<Param>& params) const;
	virtual bool get_param(Param& p) const;
};
struct AstStatementList : public AstNode {
	~AstStatementList();
	std::string repr() const;
	bool emit(Compiler& c) const;

	std::vector<AstNode*> nodes;
	
};
struct AstAssign : public AstNode {
	AstAssign(AstNode *s, AstNode *d);
	~AstAssign();
	std::string repr() const;
	bool emit(Compiler& c) const;

	AstNode *src, *dst;
};
struct AstIdentifier : public AstNode {
	AstIdentifier(const std::string& s);
	std::string repr() const;
	bool emit(Compiler& c) const;
	bool emit_lvalue(Compiler& c) const;
	bool get_param(Param& p) const;

	std::string name;
};
struct AstCall : public AstNode {
	AstCall(AstNode* n, const std::vector<AstNode*>& p);
	~AstCall();
	std::string repr() const;
	bool emit(Compiler& c) const;

	std::vector<AstNode*> params;
	AstNode* node;
};
struct AstConstant : public AstNode {
	enum Type {
		INT,
	};
	AstConstant(Type t, const char *begin, const char *end);
	std::string repr() const;
	bool emit(Compiler& c) const;

	Type type;
	union {
		int _int;
	} value;
};
struct AstBinOp : public AstNode {
	AstBinOp(Token::Type type, AstNode *l, AstNode *r);
	~AstBinOp();
	std::string repr() const;
	bool emit(Compiler& c) const;

	AstNode *left, *right;
	Token::Type type;
};
struct AstUnaryOp : public AstNode {
	AstUnaryOp(Token::Type type, AstNode *n);
	~AstUnaryOp();
	std::string repr() const;
	bool emit(Compiler& c) const;

	AstNode *node;
	Token::Type type;
};
struct AstTernaryOp : public AstNode {
	AstTernaryOp(AstNode *c, AstNode *t, AstNode *f);
	~AstTernaryOp();
	std::string repr() const;
	bool emit(Compiler& c) const;
	bool emit_lvalue(Compiler& c) const;

	AstNode *cond, *true_node, *false_node;
};
struct AstMember : public AstNode {
	AstMember(AstNode *n, const std::string& s);
	~AstMember();
	std::string repr() const;
	bool emit(Compiler& c) const;
	bool emit_lvalue(Compiler& c) const;

	std::string name;
	AstNode *node;
};
struct AstLambda : public AstNode {
	AstLambda(const std::vector<Param>& p, AstNode *b);
	~AstLambda();
	std::string repr() const;
	bool emit(Compiler& c) const;

	std::vector<Param> params;
	AstNode *body;
};
struct AstTuple : public AstNode {
	AstTuple(const std::vector<AstNode*>& n);
	~AstTuple();
	std::string repr() const;
	bool emit(Compiler& c) const;
	bool get_params(std::vector<Param>& params) const;

	std::vector<AstNode*> nodes;
};

} }

#endif