object P025A {
  def main(args: Array[String]) = {
    val n = readInt
    val a = readLine.split(' ').map(x => x.toInt).map(x => x % 2)
    val parity = if (a.reduceLeft(_ + _) > 1) 0 else 1
    println(a.indexOf((a.filter(x => x % 2 == parity))(0)) + 1)
  }
}
