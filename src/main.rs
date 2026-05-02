mod network;

fn main() {
    let a = network::packet::Packet::new(1, vec![1]);
    println!("{:?}", a);
}
