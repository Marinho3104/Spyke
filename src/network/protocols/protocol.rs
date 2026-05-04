use std::convert::TryFrom;

use crate::network::packet::Packet;

pub(crate) trait Protocol : TryFrom<Packet> {

}
