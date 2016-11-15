object P037A extends App {
  val n = readInt
  val a = readLine.split(' ').map(_.toInt)
  val b = a.groupBy(identity).map(x => (x._1, x._2.size))
  printf("%d %d\n", b.maxBy(x => x._2)._2, b.size)
}
