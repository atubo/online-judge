object P027A {
  def main(args: Array[String]) = {
    var s = scala.collection.mutable.Set((1 to readInt+1) :_*)
    readLine.split(' ').map(x => x.toInt).foreach(x => s.remove(x))
    println(s min)
  }
}
