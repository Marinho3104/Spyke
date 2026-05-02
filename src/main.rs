mod network;

fn main() {
    let a = network::packet::Packet::new(1, vec![1; 513]);
    match a {
	Ok(value) => {
	    println!("{:?}", value);
	    println!("{} and {:?}", value.protocol_id(), value.payload())
	},
	Err(value) => {
	    println!("Error {}", value)
	}
    }
}
