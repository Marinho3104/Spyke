
macro_rules! log_info {
    ($($arg:tt)*) => {
	#[cfg(debug_assertions)]
	{
	    println!("[{}:{}]: (INFO) {}", std::file!(), std::line!(), format_args!($($arg)*));
	}
    };
}
pub(crate) use log_info;

macro_rules! log_success {
    ($($arg:tt)*) => {
	#[cfg(debug_assertions)]
	{
	    println!("[{}:{}]: (SUCCESS) {}", std::file!(), std::line!(), format_args!($($arg)*));
	}
    };
}
pub(crate) use log_success;

macro_rules! log_error {
    ($($arg:tt)*) => {
	{
	    println!("[{}:{}]: (ERROR) {}", std::file!(), std::line!(), format_args!($($arg)*));
	}
    };
}
pub(crate) use log_error;
