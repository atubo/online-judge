object P033C extends App {
  val n = readInt
  val a = readLine.split(' ').map(_.toInt)
  val f = (a: Array[Int]) => a.map(-_*2).scan(0)(_+_).scan(0)(math.max(_,_)).drop(1)
  val pb = f(a)
  val sb = f(a.reverse).reverse
  println(a.fold(0)(_+_) + pb.zip(sb).map(x => x._1+x._2).max)
}
