object P049D extends App {
  val n = readInt
  val a = readLine.zipWithIndex
  val c1e = a.count(x => (x._1 == '1' && x._2 % 2 == 0))
  val c1o = a.count(x => (x._1 == '1' && x._2 % 2 == 1))
  val c0e = a.count(x => (x._1 == '0' && x._2 % 2 == 0))
  val c0o = a.count(x => (x._1 == '0' && x._2 % 2 == 1))
  println(math.min(c1e + c0o, c1o + c0e))
}
