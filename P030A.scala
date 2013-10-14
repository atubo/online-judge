object P030A {
  def errorOut():Unit = {
    println("No solution")
    System.exit(0)
  }
  def earlyOut(x: Int): Unit = {
    println(x);
    System.exit(0);
  }
  def solve(y: Int, n: Int): Int = {
    return math.round(math.exp(math.log(y)/n)).toInt;
  }
  def pow(x: Int, n: Int):Int = {
    var y = 1
    for (i <- 1 to n) y *= x
    return y
  }
  def main(args: Array[String]) = {
    val Array(a, b, n) = readLine.split(" ").map(_.toInt)
    if (a == 0 && b != 0) errorOut();
    if (a == 0 && b == 0) earlyOut(1);
    if (b % a != 0) errorOut();
    val y = b/a;
    if (y == 0) earlyOut(0);
    if (y < 0 && n % 2 == 0) errorOut();
    val x = if (y > 0) solve(y, n) else -solve(-y, n)
    if (pow(x, n) != y) errorOut();
    println(x)
  }
}
