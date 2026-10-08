use std::collections::LinkedList;

#[derive(Clone)]
pub struct Node<T> {
    pub value: T,
    pub r#type: String,
}

pub fn tree<T>(node: *mut Node<T>)-> *mut Node<T>{
    node
}

fn main() {
    let mut _list: LinkedList<Node<i64>> = LinkedList::new();
    let mut r1used = false;
    let mut r1: f64 = 0.0;
    let equation = "987+/|52/3+2|/+3";
    
    let mut chars = equation.chars().peekable();

    while let Some(c) = chars.next() {
        if c.is_numeric() {
            r1used = true;
            r1 = r1 * 10.0 + c.to_digit(10).expect("") as f64;
        } else {
            if r1used {
                print!("{} ", r1);
            }
            r1 = 0.0;
            r1used = false;

            match c {
                '+' => print!("add "),
                '/' => {
                    if chars.peek() == Some(&'|') {
                        print!("s d ");
                    } else {
                        print!("m d ")
                    }
                }
                '|' => {
                    match chars.peek() {
                        Some('/') => print!("e d "),
                        _ => {},
                    }
                },
                '%' => print!("mod"),
                _ => print!(""),
            }
        }
    }

    if r1used {
        print!("{}", r1);
    }
}