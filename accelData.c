/*
 * File:   accelData.c
 * Author: DT04
 *
 * Created on February 20, 2017, 2:42 PM
 */
#include "accelData.h"


unsigned char newAccel[ACCEL_DATA_LEN] = {
66,
38,
92,
38,
124,
38,
94,
38,
92,
38,
106,
38,
94,
38,
119,
38,
144,
38,
150,
38,
196,
38,
184,
38,
218,
38,
209,
38,
208,
38,
184,
38,
157,
38,
158,
38,
162,
38,
142,
38,
141,
38,
138,
38,
111,
38,
101,
38,
77,
38,
83,
38,
86,
38,
111,
38,
126,
38,
169,
38,
197,
38,
224,
38,
210,
38,
234,
38,
241,
38,
173,
38,
192,
38,
122,
38,
75,
38,
101,
38,
100,
38,
98,
38,
149,
38,
140,
38,
172,
38,
176,
38,
145,
38,
154,
38,
149,
38,
133,
38,
165,
38,
158,
38,
198,
38,
176,
38,
179,
38,
154,
38,
83,
38,
100,
38,
17,
38,
28,
38,
53,
38,
76,
38,
109,
38,
187,
38,
182,
38,
248,
38,
5,
39,
237,
38,
10,
39,
240,
38,
203,
38,
217,
38,
170,
38,
141,
38,
123,
38,
100,
38,
49,
38,
44,
38,
44,
38,
54,
38,
76,
38,
111,
38,
119,
38,
149,
38,
176,
38,
179,
38,
223,
38,
245,
38,
223,
38,
240,
38,
205,
38,
205,
38,
198,
38,
152,
38,
127,
38,
123,
38,
52,
38,
73,
38,
75,
38,
41,
38,
83,
38,
90,
38,
79,
38,
133,
38,
153,
38,
171,
38,
194,
38,
192,
38,
205,
38,
202,
38,
200,
38,
203,
38,
208,
38,
164,
38,
151,
38,
133,
38,
114,
38,
104,
38,
75,
38,
69,
38,
91,
38,
94,
38,
89,
38,
128,
38,
121,
38,
134,
38,
170,
38,
163,
38,
202,
38,
214,
38,
189,
38,
192,
38,
193,
38,
150,
38,
148,
38,
153,
38,
111,
38,
115,
38,
105,
38,
64,
38,
69,
38,
96,
38,
94,
38,
73,
38,
133,
38,
115,
38,
166,
38,
169,
38,
156,
38,
183,
38,
190,
38,
159,
38,
190,
38,
198,
38,
128,
38,
168,
38,
127,
38,
93,
38,
114,
38,
101,
38,
89,
38,
101,
38,
98,
38,
84,
38,
111,
38,
121,
38,
147,
38,
138,
38,
159,
38,
167,
38,
148,
38,
186,
38,
147,
38,
161,
38,
178,
38,
132,
38,
146,
38,
145,
38,
97,
38,
101,
38,
116,
38,
92,
38,
133,
38,
104,
38,
88,
38,
151,
38,
142,
38,
131,
38,
172,
38,
150,
38,
165,
38,
154,
38,
159,
38,
171,
38,
151,
38,
139,
38,
153,
38,
138,
38,
109,
38,
101,
38,
126,
38,
108,
38,
99,
38,
149,
38,
113,
38,
137,
38,
149,
38,
91,
38,
163,
38,
159,
38,
132,
38,
216,
38,
125,
38,
144,
38,
192,
38,
134,
38,
163,
38,
162,
38,
95,
38,
124,
38,
134,
38,
81,
38,
121,
38,
114,
38,
120,
38,
129,
38,
118,
38,
130,
38,
155,
38,
148,
38,
143,
38,
160,
38,
137,
38,
156,
38,
175,
38,
134,
38,
143,
38,
167,
38,
107,
38,
142,
38,
130,
38,
94,
38,
134,
38,
122,
38,
84,
38,
136,
38,
144,
38,
94,
38,
168,
38,
123,
38,
118,
38,
175,
38,
139,
38,
120,
38,
161,
38,
137,
38,
132,
38,
173,
38,
105,
38,
138,
38,
126,
38,
83,
38,
122,
38,
105,
38,
79,
38,
132,
38,
123,
38,
87,
38,
164,
38,
138,
38,
112,
38,
186,
38,
129,
38,
129,
38,
172,
38,
107,
38,
143,
38,
157,
38,
116,
38,
140,
38,
138,
38,
97,
38,
111,
38,
137,
38,
99,
38,
135,
38,
151,
38,
113,
38,
139,
38,
180,
38,
96,
38,
139,
38,
145,
38,
120,
38,
180,
38,
127,
38,
74,
38,
171,
38,
94,
38,
91,
38,
170,
38,
89,
38,
130,
38,
159,
38,
97,
38,
125,
38,
166,
38,
114,
38,
155,
38,
174,
38,
112,
38,
179,
38,
151,
38,
100,
38,
157,
38,
128,
38,
92,
38,
148,
38,
142,
38,
89,
38,
164,
38,
104,
38,
99,
38,
132,
38,
98,
38,
101,
38,
132,
38,
103,
38,
110,
38,
163,
38,
116,
38,
125,
38,
169,
38,
116,
38,
152,
38,
171,
38,
111,
38,
154,
38,
144,
38,
106,
38,
134,
38,
120,
38,
77,
38,
91,
38,
120,
38,
120,
38,
146,
38,
123,
38,
116,
38,
154,
38,
126,
38,
136,
38,
167,
38,
148,
38,
146,
38,
148,
38,
141,
38,
150,
38,
165,
38,
119,
38,
162,
38,
128,
38,
123,
38,
116,
38,
118,
38,
106,
38,
140,
38,
116,
38,
104,
38,
130,
38,
111,
38,
114,
38,
166,
38,
135,
38,
149,
38,
142,
38,
118,
38,
152,
38,
150,
38,
125,
38,
137,
38,
132,
38,
103,
38,
146,
38,
125,
38,
94,
38,
139,
38,
123,
38,
92,
38,
140,
38,
135,
38,
116,
38,
164,
38,
138,
38,
136,
38,
174,
38,
114,
38,
148,
38,
172,
38,
114,
38,
98,
38,
138,
38,
118,
38,
133,
38,
137,
38,
125,
38,
111,
38,
135,
38,
99,
38,
87,
38,
147,
38,
133,
38,
111,
38,
154,
38,
121,
38,
135,
38,
154,
38,
130,
38,
140,
38,
171,
38,
80,
38,
164,
38,
144,
38,
99,
38,
173,
38,
115,
38,
104,
38,
130,
38,
123,
38,
121,
38,
166,
38,
116,
38,
121,
38,
162,
38,
117,
38,
143,
38,
153,
38,
122,
38,
138,
38,
158,
38,
153,
38,
131,
38,
138,
38,
104,
38,
113,
38,
135,
38,
91,
38,
101,
38,
136,
38,
89,
38,
146,
38,
125,
38,
120,
38,
144,
38,
156,
38,
120,
38,
209,
38,
128,
38,
181,
38,
197,
38,
181,
38,
159,
38,
183,
38,
104,
38,
164,
38,
135,
38,
110,
38,
132,
38,
79,
38,
88,
38,
105,
38,
71,
38,
76,
38,
100,
38,
81,
38,
100,
38,
118,
38,
113,
38,
123,
38,
150,
38,
150,
38,
148,
38,
187,
38,
144,
38,
153,
38,
191,
38,
131,
38,
138,
38,
137,
38,
103,
38,
129,
38,
119,
38,
75,
38,
104,
38,
92,
38,
89,
38,
121,
38,
109,
38,
138,
38,
158,
38,
144,
38,
168,
38,
161,
38,
156,
38,
159,
38,
144,
38,
147,
38,
155,
38,
111,
38,
142,
38,
135,
38,
116,
38,
125,
38,
94,
38,
91,
38,
106,
38,
105,
38,
117,
38,
100,
38,
132,
38,
103,
38,
125,
38,
133,
38,
121,
38,
161,
38,
140,
38,
125,
38,
160,
38,
123,
38,
161,
38,
142,
38,
144,
38,
158,
38,
133,
38,
95,
38,
148,
38,
111,
38,
133,
38,
114,
38,
95,
38,
119,
38,
102,
38,
139,
38,
122,
38,
151,
38,
140,
38,
145,
38,
176,
38,
163,
38,
165,
38,
182,
38,
148,
38,
162,
38,
174,
38,
116,
38,
147,
38,
135,
38,
85,
38,
130,
38,
97,
38,
111,
38,
127,
38,
110,
38,
116,
38,
146,
38,
116,
38,
144,
38,
164,
38,
128,
38,
161,
38,
154,
38,
135,
38,
153,
38,
139,
38,
127,
38,
129,
38,
134,
38,
136,
38,
129,
38,
124,
38,
117,
38,
131,
38,
144,
38,
134,
38,
152,
38,
143,
38,
145,
38,
172,
38,
175,
38,
163,
38,
195,
38,
168,
38,
175,
38,
171,
38,
166,
38,
168,
38,
191,
38,
199,
38,
8,
39,
13,
39,
58,
39,
78,
39,
79,
39,
50,
39,
75,
39,
84,
39,
178,
39,
180,
39,
114,
39,
197,
39,
225,
39,
87,
40,
69,
39,
144,
39,
205,
38,
55,
39,
78,
39,
238,
38,
133,
39,
248,
38,
221,
39,
95,
39,
1,
39,
106,
38,
141,
37,
14,
38,
203,
36,
118,
37,
158,
35,
226,
36,
71,
35,
1,
37,
193,
35,
115,
37,
185,
36,
9,
38,
108,
37,
210,
39,
82,
38,
144,
39,
33,
38,
194,
39,
209,
37,
176,
39,
33,
37,
56,
39,
235,
36,
0,
39,
177,
37,
61,
39,
242,
37,
42,
39,
27,
38,
176,
38,
255,
37,
140,
39,
187,
38,
192,
40,
223,
39,
17,
40,
204,
39,
167,
39,
27,
39,
161,
39,
130,
38,
206,
38,
106,
37,
42,
38,
213,
36,
239,
36,
208,
36,
137,
36,
41,
37,
170,
35,
93,
37,
4,
35,
129,
37,
71,
35,
24,
38,
38,
36,
241,
37,
162,
36,
132,
37,
14,
37,
246,
37,
209,
38,
202,
38,
124,
39,
2,
39,
210,
39,
216,
38,
211,
39,
240,
38,
12,
40,
61,
39,
75,
40,
139,
39,
71,
40,
105,
39,
242,
39,
18,
39,
155,
39,
179,
38,
220,
38,
55,
38,
46,
38,
159,
37,
164,
37,
217,
36,
15,
37,
238,
36,
104,
37,
81,
37,
125,
37,
118,
37,
209,
37,
222,
37,
67,
38,
158,
38,
2,
39,
64,
39,
95,
39,
81,
39,
53,
39,
74,
39,
1,
39,
0,
39,
3,
39,
36,
39,
212,
38,
201,
38,
93,
38,
27,
38,
222,
37,
219,
37,
232,
37,
5,
38,
252,
37,
64,
38,
55,
38,
88,
38,
111,
38,
160,
38,
195,
38,
237,
38,
250,
38,
23,
39,
18,
39,
242,
38,
220,
38,
128,
38,
112,
38,
101,
38,
98,
38,
78,
38,
60,
38,
5,
38,
249,
37,
245,
37,
17,
38,
52,
38,
101,
38,
148,
38,
173,
38,
165,
38,
194,
38,
183,
38,
207,
38,
243,
38,
212,
38,
183,
38,
211,
38,
191,
38,
205,
38,
34,
39,
165,
39,
112,
40,
161,
41,
239,
41,
59,
43,
197,
43,
95,
44,
167,
43,
179,
42,
201,
42,
255,
41,
121,
42,
3,
40,
239,
39,
141,
37,
244,
38,
48,
38,
9,
40,
64,
38,
178,
39,
221,
37,
133,
39,
223,
36,
213,
41,
85,
43,
110,
46,
0,
45,
211,
44,
56,
42,
232,
42,
220,
41,
81,
40,
38,
36,
247,
33,
105,
31,
110,
31,
21,
31,
101,
32,
185,
29,
142,
32,
80,
34,
230,
37,
80,
39,
83,
42,
160,
43,
75,
44,
108,
44,
140,
43,
132,
44,
254,
43,
150,
44,
13,
42,
97,
38,
89,
35,
248,
34,
30,
35,
137,
34,
192,
31,
48,
31,
23,
31,
31,
34,
242,
32,
156,
35,
84,
36,
107,
39,
142,
37,
30,
40,
65,
38,
159,
40,
98,
38,
152,
42,
157,
40,
190,
42,
250,
40,
244,
40,
208,
38,
37,
37,
109,
36,
153,
38,
230,
37,
42,
38,
126,
36,
129,
36,
218,
35,
44,
36,
68,
37,
250,
37,
158,
38,
227,
40,
29,
42,
32,
41,
242,
40,
205,
39,
196,
39,
132,
38,
206,
40,
199,
39,
99,
40,
177,
39,
227,
37,
89,
37,
180,
35,
122,
35,
249,
35,
231,
34,
191,
35,
100,
35,
154,
35,
168,
35,
132,
36,
31,
36,
214,
36,
45,
36,
219,
37,
73,
39,
56,
41,
31,
41,
234,
40,
229,
41,
113,
41,
149,
40,
21,
39,
50,
37,
85,
36,
159,
37,
7,
38,
96,
37,
196,
36,
82,
36,
228,
37,
178,
38,
17,
38,
143,
37,
26,
38,
221,
38,
186,
39,
154,
39,
211,
39,
2,
41,
3,
42,
143,
40,
27,
41,
200,
38,
229,
38,
236,
36,
100,
36,
205,
33,
250,
33,
34,
33,
207,
34,
2,
35,
202,
36,
77,
37,
13,
39,
2,
40,
113,
40,
212,
41,
114,
42,
121,
42,
251,
42,
215,
41,
227,
42,
25,
42,
200,
41,
8,
41,
193,
40,
161,
40,
208,
38,
78,
35,
226,
34,
120,
33,
47,
34,
243,
34,
109,
36,
243,
37,
250,
38,
115,
39,
72,
40,
151,
39,
219,
39,
29,
39,
236,
38,
149,
39,
197,
39,
113,
40,
12,
40,
245,
39,
132,
38,
7,
38,
208,
35,
221,
33,
166,
32,
200,
32,
253,
33,
133,
35,
101,
36,
119,
36,
172,
37,
75,
38,
190,
38,
183,
38,
143,
38,
19,
40,
24,
39,
110,
40,
71,
38,
71,
40,
35,
38,
168,
38,
19,
38,
236,
38,
45,
38,
61,
39,
102,
40,
39,
42,
38,
42,
77,
42,
225,
42,
17,
42,
167,
41,
69,
39,
123,
38,
155,
36,
212,
37,
218,
35,
133,
37,
202,
36,
100,
37,
38,
38,
73,
37,
205,
38,
72,
37,
12,
40,
154,
38,
25,
39,
160,
36,
70,
36,
222,
35,
74,
36,
35,
37,
221,
38,
162,
39,
190,
39,
151,
39,
65,
40,
37,
39,
96,
39,
32,
39,
104,
39,
52,
38,
82,
37,
171,
37,
110,
37,
222,
38,
36,
39,
93,
39,
54,
40,
57,
39,
127,
40,
134,
38,
109,
39,
249,
36,
121,
37,
3,
37,
24,
37,
83,
38,
92,
39,
208,
40,
18,
40,
233,
39,
215,
40,
225,
39,
217,
40,
169,
38,
209,
38,
90,
36,
49,
36,
157,
32,
91,
33,
244,
32,
177,
35,
230,
35,
129,
37,
93,
36,
132,
37,
18,
38,
186,
40,
126,
39,
146,
41,
74,
40,
177,
41,
228,
40,
11,
42,
161,
40,
180,
40,
98,
39,
66,
40,
241,
38,
49,
40,
117,
38,
183,
39,
49,
38,
254,
38,
67,
38,
129,
38,
173,
38,
28,
38,
1,
39,
169,
37,
243,
37,
113,
37,
231,
39,
241,
38,
221,
40,
131,
39,
190,
40,
156,
37,
210,
38,
118,
35,
80,
36,
9,
35,
118,
35,
202,
35,
24,
36,
64,
36,
134,
37,
151,
37,
128,
38,
8,
39,
215,
38,
88,
39,
87,
38,
155,
38,
245,
36,
165,
37,
155,
36,
154,
37,
42,
37,
75,
39,
110,
38,
171,
40,
88,
39,
17,
41,
248,
39,
19,
40,
41,
39,
237,
38,
108,
38,
188,
38,
154,
37,
71,
37,
40,
37,
203,
35,
177,
36,
69,
36,
247,
36,
160,
37,
210,
38,
40,
39,
167,
39,
131,
39,
17,
39,
53,
39,
39,
39,
31,
41,
202,
40,
109,
41,
129,
40,
159,
40,
190,
38,
38,
39,
208,
37,
61,
37,
42,
35,
74,
35,
89,
34,
90,
35,
191,
35,
26,
37,
213,
37,
34,
40,
231,
40,
244,
42,
18,
42,
64,
43,
135,
43,
50,
42,
46,
42,
58,
40,
67,
41,
51,
36,
143,
38,
209,
33,
169,
37,
143,
34,
122,
38,
162,
35,
128,
39,
194,
37,
31,
39,
183,
37,
39,
38,
254,
37,
113,
38,
105,
37,
94,
38,
57,
37,
85,
37,
225,
37,
145,
36,
101,
38,
119,
37,
181,
40,
71,
38,
123,
40,
26,
38,
220,
39,
199,
39,
187,
38,
20,
38,
92,
36,
99,
36,
134,
36,
220,
34,
180,
35,
75,
36,
227,
36,
217,
38,
67,
38,
94,
40,
201,
40,
146,
42,
203,
42,
51,
42,
160,
41,
36,
41,
117,
41,
36,
40,
93,
40,
241,
36,
154,
38,
130,
35,
110,
37,
170,
34,
214,
35,
158,
34,
179,
36,
192,
36,
100,
37,
219,
38,
245,
39,
94,
42,
192,
42,
80,
43,
217,
42,
162,
43,
174,
42,
188,
41,
253,
38,
8,
37,
29,
35,
78,
34,
49,
34,
100,
33,
87,
35,
221,
34,
78,
37,
146,
35,
61,
38,
95,
38,
231,
39,
184,
40,
63,
41,
42,
41,
194,
41,
91,
40,
136,
40,
24,
40,
61,
39,
142,
39,
17,
38,
4,
38,
240,
37,
207,
37,
112,
37,
13,
37,
231,
35,
220,
36,
65,
36,
223,
36,
228,
36,
225,
36,
153,
36,
34,
36,
27,
36,
48,
36,
82,
36,
162,
37,
58,
37,
52,
38,
234,
37,
145,
39,
164,
38,
8,
41,
252,
38,
179,
41,
238,
38,
179,
41,
164,
40,
195,
41,
23,
44,
30,
43,
21,
45,
192,
40,
193,
41,
241,
38,
124,
39,
69,
37,
2,
37,
131,
34,
179,
34,
198,
33,
41,
34,
201,
35,
245,
35,
87,
38,
18,
38,
243,
39,
8,
39,
94,
41,
226,
39,
77,
42,
49,
40,
2,
41,
53,
39,
106,
38,
244,
37,
180,
36,
58,
36,
124,
35,
172,
35,
223,
35,
224,
35,
95,
38,
125,
37,
144,
41,
251,
38,
246,
41,
105,
39,
37,
43,
243,
39,
235,
42,
89,
38,
254,
40,
214,
36,
248,
38,
121,
35,
153,
36,
104,
34,
138,
35,
43,
35,
27,
38,
142,
36,
60,
41,
64,
37,
192,
41,
142,
37,
128,
42,
88,
37,
157,
42,
183,
36,
209,
41,
178,
35,
48,
40,
109,
34,
171,
39,
119,
33,
137,
37,
235,
32,
192,
35,
69,
35,
42,
36,
104,
37,
107,
37,
198,
39,
58,
40,
176,
41,
36,
41,
49,
41,
207,
41,
75,
41,
7,
42,
99,
39,
253,
41,
199,
38,
237,
41,
253,
38,
132,
38,
73,
36,
115,
36,
105,
36,
36,
36,
103,
35,
14,
36,
190,
35,
172,
37,
28,
37,
146,
37,
190,
37,
238,
38,
5,
41,
160,
39,
126,
42,
168,
38,
96,
43,
72,
40,
195,
43,
253,
41,
135,
42,
146,
42,
43,
39,
255,
39,
220,
36,
77,
37,
119,
35,
164,
35,
63,
34,
192,
33,
110,
33,
234,
33,
178,
35,
100,
35,
112,
37,
217,
37,
190,
39,
200,
40,
97,
40,
84,
41,
3,
41,
232,
41,
190,
41,
128,
42,
97,
40,
237,
42,
122,
37,
174,
39,
120,
35,
128,
36,
235,
33,
185,
34,
25,
32,
38,
34,
184,
32,
185,
35,
115,
34,
224,
38,
111,
37,
168,
41,
108,
39,
65,
42,
129,
39,
102,
42,
178,
40,
113,
42,
80,
40,
170,
40,
176,
39,
114,
39,
106,
39,
154,
37,
97,
38,
225,
37,
172,
37,
64,
38,
150,
36,
102,
37,
68,
37,
206,
37,
191,
38,
207,
38,
245,
38,
32,
40,
49,
39,
84,
40,
105,
39,
138,
39,
196,
40,
192,
37,
59,
41,
152,
35,
26,
41,
189,
35,
103,
38,
9,
37,
76,
35,
106,
37,
3,
34,
193,
36,
17,
35,
35,
37,
236,
36,
89,
38,
194,
38,
102,
39,
201,
39,
206,
39,
249,
39,
78,
40,
232,
40,
80,
40,
212,
41,
138,
39,
99,
41,
230,
37,
255,
40,
6,
37,
55,
40,
74,
36,
132,
38,
157,
36,
128,
37,
92,
36,
203,
36,
174,
36,
26,
37,
88,
37,
207,
37,
39,
38,
56,
38,
97,
38,
37,
38,
30,
39,
236,
38,
203,
39,
235,
38,
37,
39,
183,
37,
96,
38,
180,
36,
137,
38,
9,
37,
215,
39,
136,
37,
58,
40,
94,
38,
185,
40,
81,
38,
211,
38,
89,
38,
100,
38,
14,
39,
159,
39,
80,
39,
193,
38,
124,
38,
227,
37,
91,
38,
107,
37,
130,
38,
126,
37,
252,
38,
247,
37,
222,
38,
135,
37,
59,
38,
252,
36,
191,
37,
91,
37,
31,
38,
7,
38,
77,
38,
252,
37,
26,
38,
43,
38,
100,
38,
202,
38,
150,
38,
196,
38,
69,
38,
180,
38,
181,
38,
46,
39,
0,
39,
20,
39,
161,
38,
211,
38,
252,
38,
34,
39,
50,
39,
226,
38,
149,
38,
106,
38,
104,
38,
147,
38,
146,
38,
100,
38,
52,
38,
14,
38,
45,
38,
93,
38,
137,
38,
102,
38,
76,
38,
46,
38,
142,
38,
217,
38,
222,
38,
193,
38,
115,
38,
94,
38,
148,
38,
184,
38,
202,
38,
197,
38,
88,
38,
79,
38,
90,
38,
109,
38,
188,
38,
164,
38,
106,
38,
59,
38,
68,
38,
135,
38,
72,
38,
38,
38,
9,
38,
239,
37,
76,
38,
81,
38,
73,
38,
23,
38,
234,
37,
204,
37,
220,
37,
198,
37,
249,
37,
22,
38,
215,
37,
32,
38,
26,
38,
7,
38,
154,
38,
52,
38,
185,
38,
131,
38,
216,
38,
181,
38,
66,
39,
226,
38,
66,
39,
196,
38,
63,
39,
7,
39,
12,
39,
239,
38,
222,
38,
159,
38,
248,
38,
137,
38,
35,
39,
227,
38,
208,
38,
124,
38,
58,
38,
27,
38,
18,
38,
97,
38,
55,
38,
166,
38,
56,
38,
154,
38,
68,
38,
111,
38,
198,
38,
45,
38,
80,
39,
113,
38,
217,
38,
43,
38,
93,
38,
100,
38,
156,
38,
224,
38,
7,
39,
226,
38,
167,
38,
133,
38,
221,
38,
75,
38,
112,
39,
98,
38,
14,
39,
71,
38,
82,
38,
212,
37,
213,
37,
36,
38,
243,
37,
207,
38,
61,
38,
235,
38,
175,
38,
239,
37,
22,
39,
191,
36,
69,
39,
234,
35,
22,
39,
52,
36,
234,
39,
41,
37,
33,
40,
93,
37,
72,
39,
44,
37,
192,
38,
170,
38,
175,
38,
27,
40,
97,
37,
217,
40,
109,
36,
63,
41,
80,
36,
9,
41 };
