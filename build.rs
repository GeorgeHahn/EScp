use cmake;

fn main() {
    let dst = cmake::build("libdtn");

    println!("cargo:rustc-link-search=native={}", dst.display());
    println!("cargo:rustc-link-lib=static=dtn");
}
