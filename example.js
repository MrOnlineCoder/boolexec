const NOT = "¬";
const AND = "∧";
const OR = "∨";
const XOR = "⊕";
const IMPLICATION = "→";
const EQ = "≡";
const SCHAEFFERSSTROKE = "↑";
const PIERCEARROW = "↓";
const Constants = ["0", "1"];
const Operators = [
  NOT,
  AND,
  OR,
  XOR,
  IMPLICATION,
  EQ,
  SCHAEFFERSSTROKE,
  PIERCEARROW,
];
function CurrLexeme(lexemes) {
  return lexemes.length > 0 ? lexemes[0] : "";
}
function NextLexeme(lexemes) {
  lexemes.shift();
  return CurrLexeme(lexemes);
}
function CheckLexeme(lexemes, value) {
  var curr = CurrLexeme(lexemes);
  if (curr != value) {
    if (curr == "")
      throw "Неожиданный конец выражения. Ожидалось '" + value + "'";
    throw "Ожидалось '" + value + "' вместо " + CurrLexeme(lexemes);
  }
}
function IsVariable(value) {
  return (
    value.match(/^[a-zA-Zа-яА-Я]\d*$/) != null ||
    value.match(/^[a-zA-Zа-яА-Я]<sub>\d*<\/sub>$/) != null
  );
}
function IsConstant(value) {
  return Constants.indexOf(value) > -1;
}
function IsOperator(value) {
  return value != NOT && Operators.indexOf(value) > -1;
}
function Preprocessing(lexemes) {
  for (var i = 0; i < lexemes.length; i++) {
    if (
      lexemes[i] == "•" ||
      lexemes[i] == "∧" ||
      lexemes[i] == "&" ||
      lexemes[i] == "*" ||
      lexemes[i] == "∩"
    )
      lexemes[i] = AND;
    if (
      lexemes[i] == "¬" ||
      lexemes[i] == "!" ||
      lexemes[i] == "⌐" ||
      lexemes[i] == "﹁"
    )
      lexemes[i] = NOT;
    if (lexemes[i] == "∨" || lexemes[i] == "+" || lexemes[i] == "∪")
      lexemes[i] = OR;
    if (lexemes[i] == "^" || lexemes[i] == "⊕") lexemes[i] = XOR;
    if (lexemes[i] == "->" || lexemes[i] == "→" || lexemes[i] == "=>") {
      lexemes[i] = IMPLICATION;
    }
    if (
      lexemes[i] == "~" ||
      lexemes[i] == "=" ||
      lexemes[i] == "≡" ||
      lexemes[i] == "⇔" ||
      lexemes[i] == "<=>" ||
      lexemes[i] == "↔"
    ) {
      lexemes[i] = EQ;
    }
    if (lexemes[i] == "|" || lexemes[i] == "↑" || lexemes[i] == "∣") {
      lexemes[i] = SCHAEFFERSSTROKE;
    }
    if (lexemes[i] == "↓") {
      lexemes[i] = PIERCEARROW;
    }
    if (lexemes[i].match(/^[a-zA-Zа-яА-Я]\d+$/)) {
      lexemes[i] = lexemes[i][0] + "<sub>" + lexemes[i].substr(1) + "</sub>";
    }
  }
  for (var i = 0; i < lexemes.length - 1; i++) {
    if (
      IsVariable(lexemes[i]) &&
      (IsVariable(lexemes[i + 1]) ||
        lexemes[i + 1] == NOT ||
        lexemes[i + 1] == "(")
    )
      lexemes.splice(i + 1, 0, AND);
    if (
      lexemes[i] == ")" &&
      (IsVariable(lexemes[i + 1]) ||
        lexemes[i + 1] == "(" ||
        lexemes[i + 1] == NOT)
    )
      lexemes.splice(i + 1, 0, AND);
  }
}
function FindIncorrect(text, lexemes) {
  if (lexemes == null) lexemes = [];
  var expr = lexemes.join("");
  var index = 0;
  while (index < expr.length && text[index] == expr[index]) index++;
  return text[index];
}
function Parse(text) {
  var lexemes = text.match(
    /\(|\)|[a-zA-Zа-яА-Я]\d*|∨|∪|\+|•|∧|\*|∩|&|!|¬|⌐|﹁|⊕|\^|->|→|=>|~|=|≡|⇔|↔|<=>|↓|↑|∣|\||1|0/gi
  );
  text = text.replace(/ /g, "");
  if (text == "") throw "Введённое выражение пустое";
  if (lexemes == null || lexemes.join("") != text)
    throw (
      "в выражении присутствуют недопустимые символы, например: '" +
      FindIncorrect(text, lexemes) +
      "'"
    );
  Preprocessing(lexemes);
  var func = lexemes.join("");
  var vars = [];
  var rpn = [];
  Addition(vars, rpn, lexemes);
  if (lexemes.length > 0) throw "выражение некорректно";
  vars.sort();
  return { vars: vars, rpn: rpn, func: func };
}
function Addition(vars, rpn, lexemes) {
  Addition2(vars, rpn, lexemes);
  var op = CurrLexeme(lexemes);
  while (op == EQ) {
    NextLexeme(lexemes);
    Addition2(vars, rpn, lexemes);
    rpn.push(op);
    op = CurrLexeme(lexemes);
  }
}
function Addition2(vars, rpn, lexemes) {
  Addition3(vars, rpn, lexemes);
  var op = CurrLexeme(lexemes);
  while (op == IMPLICATION) {
    NextLexeme(lexemes);
    Addition3(vars, rpn, lexemes);
    rpn.push(op);
    op = CurrLexeme(lexemes);
  }
}
function Addition3(vars, rpn, lexemes) {
  Addition4(vars, rpn, lexemes);
  var op = CurrLexeme(lexemes);
  while (op == PIERCEARROW) {
    NextLexeme(lexemes);
    Addition4(vars, rpn, lexemes);
    rpn.push(op);
    op = CurrLexeme(lexemes);
  }
}
function Addition4(vars, rpn, lexemes) {
  Addition5(vars, rpn, lexemes);
  var op = CurrLexeme(lexemes);
  while (op == SCHAEFFERSSTROKE) {
    NextLexeme(lexemes);
    Addition5(vars, rpn, lexemes);
    rpn.push(op);
    op = CurrLexeme(lexemes);
  }
}
function Addition5(vars, rpn, lexemes) {
  Addition6(vars, rpn, lexemes);
  var op = CurrLexeme(lexemes);
  while (op == SCHAEFFERSSTROKE || op == PIERCEARROW) {
    NextLexeme(lexemes);
    Addition6(vars, rpn, lexemes);
    rpn.push(op);
    op = CurrLexeme(lexemes);
  }
}
function Addition6(vars, rpn, lexemes) {
  Multiplying(vars, rpn, lexemes);
  var op = CurrLexeme(lexemes);
  while (op == OR || op == XOR) {
    NextLexeme(lexemes);
    Multiplying(vars, rpn, lexemes);
    rpn.push(op);
    op = CurrLexeme(lexemes);
  }
}
function Multiplying(vars, rpn, lexemes) {
  Entity(vars, rpn, lexemes);
  while (CurrLexeme(lexemes) == AND) {
    var operation = CurrLexeme(lexemes);
    NextLexeme(lexemes);
    Entity(vars, rpn, lexemes);
    rpn.push(operation);
  }
}
function Entity(vars, rpn, lexemes) {
  var lexeme = CurrLexeme(lexemes);
  if (lexeme == "(") {
    NextLexeme(lexemes);
    Addition(vars, rpn, lexemes);
    CheckLexeme(lexemes, ")");
    NextLexeme(lexemes);
  } else if (IsConstant(lexeme)) {
    rpn.push(CurrLexeme(lexemes));
    NextLexeme(lexemes);
  } else if (IsVariable(lexeme)) {
    if (vars.indexOf(lexeme) == -1) vars.push(lexeme);
    rpn.push(lexeme);
    NextLexeme(lexemes);
  } else if (lexeme == NOT) {
    NextLexeme(lexemes);
    Entity(vars, rpn, lexemes);
    rpn.push(NOT);
  } else {
    throw "некорректный символ в выражении: '" + lexeme + "'";
  }
}
function Calculate(vars, var_values, rpn) {
  var stack = [];
  for (var i = 0; i < rpn.length; i++) {
    if (IsConstant(rpn[i])) {
      stack.unshift(rpn[i]);
    } else if (IsVariable(rpn[i])) {
      stack.unshift(var_values[vars.indexOf(rpn[i])]);
    } else if (IsOperator(rpn[i])) {
      var arg2 = +stack.shift();
      var arg1 = +stack.shift();
      if (rpn[i] == AND) {
        stack.unshift(arg1 & arg2);
      } else if (rpn[i] == OR) {
        stack.unshift(arg1 | arg2);
      } else if (rpn[i] == XOR) {
        stack.unshift(arg1 ^ arg2);
      } else if (rpn[i] == IMPLICATION) {
        stack.unshift(!arg1 | arg2);
      } else if (rpn[i] == EQ) {
        stack.unshift((1 - arg1) ^ arg2);
      } else if (rpn[i] == PIERCEARROW) {
        stack.unshift(1 - (arg1 | arg2));
      } else if (rpn[i] == SCHAEFFERSSTROKE) {
        stack.unshift(1 - (arg1 & arg2));
      }
    } else if (rpn[i] == NOT) {
      var arg = stack.shift();
      stack.unshift(1 - arg);
    }
  }
  return stack.shift();
}
function GetTree(rpn) {
  var stack = [];
  for (var i = 0; i < rpn.length; i++) {
    var node = { v: rpn[i], left: null, right: null };
    if (IsConstant(rpn[i]) || IsVariable(rpn[i])) {
    } else if (IsOperator(rpn[i])) {
      node.right = stack.shift();
      node.left = stack.shift();
    } else if (rpn[i] == NOT) {
      node.left = stack.shift();
    }
    stack.unshift(node);
  }
  return stack.shift();
}
function GetSub(tree) {
  if (tree == null) return [];
  if (tree.left == null && tree.right == null) return [tree.v];
  var left = GetSub(tree.left);
  var right = GetSub(tree.right);
  var sub = [];
  for (var i = 0; i < left.length; i++) sub.push(left[i]);
  for (var i = 0; i < right.length; i++) sub.push(right[i]);
  sub.push(tree.v);
  return sub;
}
function HaveSub(expr, sub) {
  if (
    sub.indexOf(AND) == -1 &&
    sub.indexOf(OR) == -1 &&
    sub.indexOf(XOR) == -1 &&
    sub.indexOf(NOT) == -1 &&
    sub.indexOf(IMPLICATION) == -1 &&
    sub.indexOf(EQ) == -1 &&
    sub.indexOf(SCHAEFFERSSTROKE) == -1 &&
    sub.indexOf(PIERCEARROW) == -1
  )
    return true;
  for (var i = 0; i < expr.length; i++) {
    if (expr[i].length == sub.length) {
      var j = 0;
      while (j < expr[i].length && expr[i][j] == sub[j]) j++;
      if (j == expr[i].length) return true;
    }
  }
  return false;
}
function GetSubExpr(tree, subexpr) {
  if (tree == null) return;
  var left = GetSub(tree.left);
  GetSubExpr(tree.left, subexpr);
  if (left.length > 0 && !HaveSub(subexpr, left)) subexpr.push(left);
  var right = GetSub(tree.right);
  GetSubExpr(tree.right, subexpr);
  if (right.length > 0 && !HaveSub(subexpr, right)) subexpr.push(right);
}
function RPNtoString(rpn) {
  var stack = [];
  var stackP = [];
  for (var i = 0; i < rpn.length; i++) {
    if (IsConstant(rpn[i]) || IsVariable(rpn[i])) {
      stack.unshift(rpn[i]);
      stackP.unshift(0);
    } else if (IsOperator(rpn[i])) {
      var arg2 = stack.shift();
      var arg1 = stack.shift();
      var p2 = stackP.shift();
      var p1 = stackP.shift();
      var p;
      if (rpn[i] == AND) {
        p = 2;
      } else {
        p = 1;
      }
      if (p1 > 0 && p1 < p) {
        arg1 = "(" + arg1 + ")";
      }
      if (p2 > 0 && p2 <= p) {
        arg2 = "(" + arg2 + ")";
      }
      stack.unshift(arg1 + rpn[i] + arg2);
      stackP.unshift(p);
    } else if (rpn[i] == NOT) {
      var arg = stack.shift();
      var p = stackP.shift();
      stack.unshift(MakeNot(arg));
      stackP.unshift(0);
    }
  }
  return stack.shift();
}
