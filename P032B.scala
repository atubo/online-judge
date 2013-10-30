object P032B extends App {
  def f(a: List[Char]):Unit = a match {
    case '.'::tail => print(0); f(tail)
    case '-'::'.'::tail => print(1); f(tail)
    case '-'::'-'::tail => print(2); f(tail)
    case Nil =>
  }
  f(readLine.toList)
}

