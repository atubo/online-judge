object P039F extends App {
  readLine()
  val frog = readLine().split(' ').map(_.toInt)
  val mosq = readLine().split(' ').map(_.toInt)
  val killed = frog.map(x => (mosq.count(_ % x == 0)))
  val minValue = killed.min
  val cand = killed.zipWithIndex.filter(_._1 == minValue)
  println(cand.size)
  cand.foreach(x => printf("%d ", x._2+1))
}
