object P026D {
  def main(args: Array[String]) = {
    val a = readLine.split(' ').map(x => x.toInt)
    println(math.max(0, 1- ((((a(1)-a(2)) to a(1)) zip ((a(0)+1) to (a(0)+a(2)+1)) toList).map(x => x._1*1.0/x._2) reduceLeft(_*_))))
  }
}
