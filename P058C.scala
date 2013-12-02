object P058C extends App {
  val n = readInt
  val a = readLine.split(' ').map(_.toInt)
  val target = List.range(0, n).map(i => if (i <= (n-1)/2) i+1 else n-i)
  val m = collection.mutable.Map[Int, Int]()
  a.zip(target).foreach(x=>m.update(x._1-x._2, m.getOrElse(x._1-x._2, 0)+1))
  var maxval = 0
  for (k <- m.keys) {
    if (k >= 0 && m(k) > maxval) {
      maxval = m(k)
    }
  }
  println(n-maxval)
}
