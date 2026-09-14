import streamlit as st
from pathlib import Path
import streamlit.components.v1 as components

st.set_page_config(
    page_title="Shadow Sprint",
    page_icon="🎮",
    layout="centered"
)

st.title("🎮 Shadow Sprint")
st.caption("Press SPACE to jump. Avoid the obstacles and beat your score.")

html_file = Path(__file__).parent / "index.html"

with open(html_file, "r", encoding="utf-8") as f:
    index_html = f.read()

components.html(index_html, height=500, scrolling=False)
